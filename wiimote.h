/*
 * wiimote.h
 */

/*-
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
 */

#ifndef _WIIMOTE_H
#define _WIIMOTE_H 1

#define WIIMOTE_LED_1 0x10
#define WIIMOTE_LED_2 0x20
#define WIIMOTE_LED_3 0x40
#define WIIMOTE_LED_4 0x80

#define WIIMOTE_BUTTON_2 0x0001
#define WIIMOTE_BUTTON_1 0x0002
#define WIIMOTE_BUTTON_B 0x0004
#define WIIMOTE_BUTTON_A 0x0008
#define WIIMOTE_BUTTON_MINUS 0x0010
#define WIIMOTE_BUTTON_HOME 0x0080
#define WIIMOTE_BUTTON_LEFT 0x0100
#define WIIMOTE_BUTTON_RIGHT 0x0200
#define WIIMOTE_BUTTON_DOWN 0x0400
#define WIIMOTE_BUTTON_UP 0x0800
#define WIIMOTE_BUTTON_PLUS 0x1000

#define WIIMOTE_MOTION_X_ZERO 0x8a
#define WIIMOTE_MOTION_Y_ZERO 0x84
#define WIIMOTE_MOTION_Z_ZERO 0x9c

#define WIIMOTE_N_IR 4

#define WIIMOTE_MOVEMENT_MIN 1
#define WIIMOTE_MOVEMENT_POINTING 1
#define WIIMOTE_MOVEMENT_TILTING 2
#define WIIMOTE_MOVEMENT_MAX 2

#define WIIMOTE_USLEEP 10000

#define RESOLUTION_MIN 1
#define RESOLUTION_MAX 10


void SetLED(int temp_ctrl, int temp_num);
void SetTiltSensor(int temp_ctrl);
void SetIRSensor(int temp_ctrl);

typedef struct {
    int32_t x;
    int32_t y;
    int32_t strength;
    int32_t pre_x;
    int32_t pre_y;
    int32_t pre_strength;
} IRData;

extern int movement_val;

#endif
