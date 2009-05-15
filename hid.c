/*
 * hid.c
 */

/*-
 * Copyright (c) 2006 Maksim Yevmenkin <m_evmenkin@yahoo.com>
 * All rights reserved.
 *
 * Copyright (c) 2007 Chuan-Heng Hsiao <hsiao.chuanheng@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: hid.c 19 2007-05-04 21:59:28Z chhsiao $
 * $FreeBSD: src/usr.sbin/bluetooth/bthidd/hid.c,v 1.2.2.3 2006/10/12 23:08:14 markus Exp $
 */

#include <sys/consio.h>
#include <sys/mouse.h>
#include <sys/queue.h>
#include <assert.h>
#include <bluetooth.h>
#include <dev/usb/usb.h>
#include <dev/usb/usbhid.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <usbhid.h>
#include "bsdmote_config.h"
#include "bsdmoted.h"
#include "kbd.h"
#include "wiimote.h"

#undef	min
#define	min(x, y)	((x) < (y) ? (x) : (y))

#undef	max
#define	max(x, y)	((x) > (y) ? (x) : (y))

#undef	ASIZE
#define	ASIZE(a)	(sizeof(a)/sizeof(a[0]))

/*
 * Process data from control channel
 */

/*
 * tilting motion movement data
 */
int32_t current_motion_x;
int32_t current_motion_y;
int32_t current_motion_z;

int32_t center_motion_x = WIIMOTE_MOTION_X_ZERO;
int32_t center_motion_y = WIIMOTE_MOTION_Y_ZERO;
int32_t center_motion_z = WIIMOTE_MOTION_Z_ZERO;

int32_t resolution_motion = 1;

char if_motion_first = 1;

/*
int32_t pre_motion_x;
int32_t pre_motion_y;
int32_t pre_motion_z;
*/

/*
 * ir movement data
 */
int32_t current_ir_x = 0;
int32_t current_ir_y = 0;

IRData ir[WIIMOTE_N_IR];

int32_t pre_ir_x = 0;
int32_t pre_ir_y = 0;

int32_t resolution_ir = 1;

/*
 * button
 */

int pre_button_val = 0;

int if_first = 1;

int32_t
hid_control(bthid_session_p s, uint8_t *data, int32_t len)
{
    //syslog(LOG_CRIT, "hid::hid_control: start");
    assert(s != NULL);
    assert(data != NULL);
    assert(len > 0);

    switch (data[0] >> 4) {
    case 0: /* Handshake (response to command) */
        if (data[0] & 0xf)
            syslog(LOG_ERR, "Got handshake message with error " \
                   "response 0x%x from %s",
                   data[0], bt_ntoa(&s->bdaddr, NULL));
        break;

    case 1: /* HID Control */
        switch (data[0] & 0xf) {
        case 0: /* NOP */
            break;

        case 1: /* Hard reset */
        case 2: /* Soft reset */
            syslog(LOG_WARNING, "Device %s requested %s reset",
                   bt_ntoa(&s->bdaddr, NULL),
                   ((data[0] & 0xf) == 1)? "hard" : "soft");
            break;

        case 3: /* Suspend */
            syslog(LOG_NOTICE, "Device %s requested Suspend",
                   bt_ntoa(&s->bdaddr, NULL));
            break;

        case 4: /* Exit suspend */
            syslog(LOG_NOTICE, "Device %s requested Exit Suspend",
                   bt_ntoa(&s->bdaddr, NULL));
            break;

        case 5: /* Virtual cable unplug */
            syslog(LOG_NOTICE, "Device %s unplugged virtual cable",
                   bt_ntoa(&s->bdaddr, NULL));
            session_close(s);
            break;

        default:
            syslog(LOG_WARNING, "Device %s sent unknown " \
                   "HID_Control message 0x%x",
                   bt_ntoa(&s->bdaddr, NULL), data[0]);
            break;
        }
        break;

    default:
        syslog(LOG_WARNING, "Got unexpected message 0x%x on Control " \
               "channel from %s", data[0], bt_ntoa(&s->bdaddr, NULL));
        break;
    }

    return (0);
}

/*
 * Process data from the interrupt channel
 */

int32_t
hid_interrupt(bthid_session_p s, uint8_t *data, int32_t len)
{
    hid_device_p	hid_device;
    hid_data_t	d;
    hid_item_t	h;
    int32_t		report_id, usage, page, val,
        mouse_x, mouse_y, mouse_z, mouse_butt,
        mevents, kevents;

    uint8_t *p_data;

    int i;

    int button_val;
    int temp_max_strength;

    char if_movement_tilting = 0;
    char if_movement_pointing = 0;

    //char temp_char[10000];
    //char *p_temp_char;
    

    report_id = 0;

    assert(s != NULL);
    assert(s->srv != NULL);
    assert(data != NULL);

    /*
    p_temp_char = temp_char;
    p_data = data;

    for(i = 0; i < len; i++) {
        sprintf(p_temp_char, "%04X ", p_data[0]);
        p_temp_char += 5;
        p_data++;
    }
    p_temp_char[0] = 0;
    syslog(LOG_CRIT, "hid::hid_interrupt: start: len: %d %s", len, temp_char);
    */

    if (len < 3) {
        syslog(LOG_ERR, "Got short message (%d bytes) on Interrupt " \
               "channel from %s", len, bt_ntoa(&s->bdaddr, NULL));
        return (-1);
    }

    if (data[0] != 0xa1) {
        syslog(LOG_ERR, "Got unexpected message 0x%x on " \
               "Interrupt channel from %s",
               data[0], bt_ntoa(&s->bdaddr, NULL));
        return (-1);
    }

    hid_device = get_hid_device(&s->bdaddr);
    assert(hid_device != NULL);

    mouse_x = mouse_y = mouse_z = mouse_butt = mevents = kevents = 0;

    //button
    button_val = data[2] * 256 + data[3];
    //syslog(LOG_CRIT, "hid::hid_interrupt: button_val: %04x", button_val);
    if(button_val & WIIMOTE_BUTTON_A && !(pre_button_val & WIIMOTE_BUTTON_A)) {
        mouse_butt |= 1;
        mevents++;
    }

    if(button_val & WIIMOTE_BUTTON_B && !(pre_button_val & WIIMOTE_BUTTON_B)) {
        mouse_butt |= 4;
        mevents++;
    }

    if_movement_pointing = button_val & WIIMOTE_BUTTON_1;
    if_movement_tilting = button_val & WIIMOTE_BUTTON_2;
    if(if_movement_tilting && !if_movement_pointing)
        movement_val = WIIMOTE_MOVEMENT_TILTING;
    else if(if_movement_pointing && !if_movement_tilting)
        movement_val = WIIMOTE_MOVEMENT_POINTING;

    //resolution
    if(button_val & WIIMOTE_BUTTON_PLUS && !(pre_button_val & WIIMOTE_BUTTON_PLUS)) {
        switch(movement_val) {
        case WIIMOTE_MOVEMENT_TILTING:
            resolution_motion--;
            resolution_motion = max(resolution_motion, RESOLUTION_MIN);
            //syslog(LOG_CRIT, "hid::hid_interrupt: resolution_motion: %d", resolution_motion);
            break;
        case WIIMOTE_MOVEMENT_POINTING:
            resolution_ir--;
            resolution_ir = max(resolution_ir, RESOLUTION_MIN);
            //syslog(LOG_CRIT, "hid::hid_interrupt: resolution_ir: %d", resolution_ir);
            break;
        default:
            break;
        }
    }
        
    if(button_val & WIIMOTE_BUTTON_MINUS && !(pre_button_val & WIIMOTE_BUTTON_MINUS)) {
        switch(movement_val) {
        case WIIMOTE_MOVEMENT_TILTING:
            resolution_motion++;
            resolution_motion = min(resolution_motion, RESOLUTION_MAX);
            //syslog(LOG_CRIT, "hid::hid_interrupt: resolution_motion: %d", resolution_motion);
            break;
        case WIIMOTE_MOVEMENT_POINTING:
            resolution_ir++;
            resolution_ir = min(resolution_ir, RESOLUTION_MAX);
            //syslog(LOG_CRIT, "hid::hid_interrupt: resolution_ir: %d", resolution_ir);
            break;
        default:
            break;
        }
    }


    //tilting
    current_motion_x = data[4];
    current_motion_y = data[5];
    current_motion_z = data[6];

    //pointing
    p_data = &data[7];

    for(i = 0; i < WIIMOTE_N_IR; i++, p_data += 3) {
        if(!(p_data[0] == 0xff && p_data[1] == 0xff)) {
            ir[i].x = p_data[0] + ((p_data[2] >> 4) & 0x03) * 256;
            ir[i].y = p_data[1] + ((p_data[2] >> 6) & 0x03) * 256;
            ir[i].strength = p_data[2] & 0x0f;
        }
        else {
            ir[i].x = 0;
            ir[i].y = 0;
            ir[i].strength = 0;
        }
    }

    temp_max_strength = 0;
    for(i = 0; i < WIIMOTE_N_IR; i++) {
        if(ir[i].strength > temp_max_strength) {
            temp_max_strength = ir[i].strength;
            if(ir[i].pre_strength != 0) {
                current_ir_x = ir[i].x;
                current_ir_y = ir[i].y;
                pre_ir_x = ir[i].pre_x;
                pre_ir_y = ir[i].pre_y;
            }
            else {
                current_ir_x = 0;
                current_ir_y = 0;
                pre_ir_x = 0;
                pre_ir_y = 0;
            }
        }
    }

    /*
    syslog(LOG_CRIT, "hid::hid_interrupt: ir: (%3d,%3d) pre: (%3d,%3d) mouse: (%3d,%3d) data: (%3x,%3x,%3x) (%3x,%3x,%3x) (%3x,%3x,%3x) (%3x,%3x,%3x)", 
           current_ir_x, current_ir_y, 
           pre_ir_x, pre_ir_y,
           -current_ir_x + pre_ir_x, current_ir_y - pre_ir_y, 
           data[7], data[8], data[9], 
           data[10], data[11], data[12], 
           data[13], data[14], data[15],
           data[16], data[17], data[18]);
    */

    mouse_x = 0;
    mouse_y = 0;
    mouse_z = 0;
    switch(movement_val) {
    case WIIMOTE_MOVEMENT_TILTING:
        if(if_motion_first) {
            if_motion_first = 0;
            center_motion_x = current_motion_x;
            center_motion_y = current_motion_y;
        }
        mouse_x = current_motion_x - center_motion_x;
        mouse_y = current_motion_y - center_motion_y;

        mouse_x /= resolution_motion;
        mouse_y /= resolution_motion;
        mevents++;
        //mouse_z = current_motion_z - 0x9c;
        break;
    case WIIMOTE_MOVEMENT_POINTING:
        mouse_x = -current_ir_x + pre_ir_x;
//     	 mouse_x = -current_ir_x;
        mouse_y = current_ir_y - pre_ir_y;
//        mouse_y = current_ir_y;
        
        mouse_x /= resolution_ir;
        mouse_y /= resolution_ir;

        if(temp_max_strength > 0 && (mouse_x || mouse_y))
            mevents++;
        break;
    default:
        break;
    }

    //set pre.
    for(i = 0; i < WIIMOTE_N_IR; i++) {
        ir[i].pre_x = ir[i].x;
        ir[i].pre_y = ir[i].y;
        ir[i].pre_strength = ir[i].strength;
    }

    pre_button_val = button_val;


    for (d = hid_start_parse(hid_device->desc, 1 << hid_input, -1);
         hid_get_item(d, &h) > 0; ) {

        page = HID_PAGE(h.usage);
        usage = HID_USAGE(h.usage);
        val = hid_get_data(data, &h);

        //syslog(LOG_CRIT, "hid::hid_interrupt: page: %d HUP_GENERIC_DESKTOP: %d HUP_KEYBOARD: %d HUP_BUTTON: %d HUP_CONSUMER: %d HUP_MICROSOFT: %d", page, HUP_GENERIC_DESKTOP, HUP_KEYBOARD, HUP_BUTTON, HUP_CONSUMER, HUP_MICROSOFT);
    }
    hid_end_parse(d);

    /* 
     * XXX FIXME Feed mouse events into kernel.
     * The code block below works, but it is not good enough.
     * Need to track double-clicks etc.
     *
     * Double click currently works in X, but not in console.
     */

    if (mevents > 0) {
        struct mouse_info	mi;


          syslog(LOG_CRIT, "hid::hid_interrupt: mouse: (%d,%d,%d) button: %d", 
          mouse_x, mouse_y, mouse_z, mouse_butt);
        
        
        mi.operation = MOUSE_ACTION;
        mi.u.data.x = mouse_x;
        mi.u.data.y = mouse_y;
        mi.u.data.z = mouse_z;
        mi.u.data.buttons = mouse_butt;

        if (ioctl(s->srv->cons, CONS_MOUSECTL, &mi) < 0)
            syslog(LOG_ERR, "Could not process mouse events from "      \
                   "%s. %s (%d)", bt_ntoa(&s->bdaddr, NULL),
                   strerror(errno), errno);
    }

    return (0);
}
