#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int /*<<< orphan*/  current_group ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  tox_group_message_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void send_irc_group(Tox *tox, uint8_t *msg, uint16_t len)
{
    if (len > 1350 || len == 0 || len == 1)
        return;

    --len;

    if (*msg != ':')
        return;

    uint8_t req[len];
    unsigned int i;

    unsigned int spaces = 0;

    for (i = 0; i < (len - 1); ++i) {
        if (msg[i + 1] == ' ') {
            ++spaces;
        } else {
            if (spaces >= 3 && msg[i + 1] == ':') {
                break;
            }
        }

        req[i] = msg[i + 1];
    }

    unsigned int req_len = i;
    req[i] = 0;

    uint8_t message[len];
    uint16_t length = 0;

    uint8_t *pmsg = (uint8_t *)strstr((char *)req, " PRIVMSG");

    if (pmsg == NULL)
        return;

    uint8_t *dt = req;

    for (dt = req, i = 0; dt != pmsg && *dt != '!'; ++dt, ++i) {
        message[i] = *dt;
        ++length;
    }

    message[length] = ':';
    length += 1;
    message[length] = ' ';
    length += 1;

    if ((req_len + 2) >= len)
        return;

    memcpy(message + length, msg + req_len + 2, len - (req_len + 2));
    length += len - (req_len + 2);
    tox_group_message_send(tox, current_group, message, length);
}