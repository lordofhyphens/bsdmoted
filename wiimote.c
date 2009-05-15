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

#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <bluetooth.h>

#include "wiimote.h"

int movement_val;

void SetTiltSensor(int temp_ctrl) { //52 12 00 31
    //syslog(LOG_CRIT, "wiimote::SetMotionSensor: start");
    char temp_cmd[4];
    int temp_int;

    usleep(WIIMOTE_USLEEP);

    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x12;
    temp_cmd[2] = 0x00;
    temp_cmd[3] = 0x31;
    temp_int = send(temp_ctrl, temp_cmd, 4, 0);

    usleep(WIIMOTE_USLEEP);

    //syslog(LOG_CRIT, "wiimote::SetMotionSensor, temp_int: %d", temp_int);
    syslog(LOG_CRIT, "wiimote::SetMotionSensor");

}


void SetLED(int temp_ctrl, int temp_num) { //52 11 number
    //syslog(LOG_CRIT, "wiimote::SetLED: start");
    char temp_cmd[3];
    int temp_int;
    temp_num = 0;
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x11;
    temp_cmd[2] = WIIMOTE_LED_1;
    temp_int = send(temp_ctrl, temp_cmd, 3, 0);
    //syslog(LOG_CRIT, "wiimote::SetLED, temp_int: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    syslog(LOG_CRIT, "wiimote::SetLED");
}

void SetIRSensor(int temp_ctrl) {
    char temp_cmd[23];
    int temp_int;

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x12;
    temp_cmd[2] = 0x00;
    temp_cmd[3] = 0x30;
    temp_int = send(temp_ctrl, temp_cmd, 4, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 1: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x13;
    temp_cmd[2] = 0x04;
    temp_int = send(temp_ctrl, temp_cmd, 3, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 2: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x1a;
    temp_cmd[2] = 0x04;
    temp_int = send(temp_ctrl, temp_cmd, 3, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 3: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    //set ir sensor memory
    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x16;
    temp_cmd[2] = 0x04;
    temp_cmd[3] = 0xb0;
    temp_cmd[4] = 0x00;
    temp_cmd[5] = 0x30;
    temp_cmd[6] = 0x01;
    temp_cmd[7] = 0x08;
    temp_int = send(temp_ctrl, temp_cmd, 23, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 4: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x16;
    temp_cmd[2] = 0x04;
    temp_cmd[3] = 0xb0;
    temp_cmd[4] = 0x00;
    temp_cmd[5] = 0x00;
    temp_cmd[6] = 0x09;
    temp_cmd[7] = 0x02;
    temp_cmd[8] = 0x00;
    temp_cmd[9] = 0x00;
    temp_cmd[10] = 0x71;
    temp_cmd[11] = 0x01;
    temp_cmd[12] = 0x00;
    temp_cmd[13] = 0xaa;
    temp_cmd[14] = 0x00;
    temp_cmd[15] = 0x64;
    temp_int = send(temp_ctrl, temp_cmd, 23, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 5: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x16;
    temp_cmd[2] = 0x04;
    temp_cmd[3] = 0xb0;
    temp_cmd[4] = 0x00;
    temp_cmd[5] = 0x1a;
    temp_cmd[6] = 0x02;
    temp_cmd[7] = 0x63;
    temp_cmd[8] = 0x03;
    temp_int = send(temp_ctrl, temp_cmd, 23, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 6: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x16;
    temp_cmd[2] = 0x04;
    temp_cmd[3] = 0xb0;
    temp_cmd[4] = 0x00;
    temp_cmd[5] = 0x33;
    temp_cmd[6] = 0x01;
    temp_cmd[7] = 0x03;
    temp_int = send(temp_ctrl, temp_cmd, 23, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 7: %d", temp_int);

    usleep(WIIMOTE_USLEEP);

    memset(temp_cmd, 0, sizeof(char) * 23);
    temp_cmd[0] = 0x52;
    temp_cmd[1] = 0x12;
    temp_cmd[2] = 0x00;
    temp_cmd[3] = 0x33;
    temp_int = send(temp_ctrl, temp_cmd, 4, 0);
    //syslog(LOG_CRIT, "wiimote::SetIRSensor: temp_int 8: %d", temp_int);
}
