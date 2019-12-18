#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {unsigned char mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  text; } ;
struct TYPE_8__ {int /*<<< orphan*/  vscroll; int /*<<< orphan*/  hscroll; int /*<<< orphan*/  position; } ;
struct TYPE_7__ {unsigned char action; int /*<<< orphan*/  position; int /*<<< orphan*/  buttons; } ;
struct TYPE_6__ {unsigned char action; int /*<<< orphan*/  metastate; int /*<<< orphan*/  keycode; } ;
struct control_msg {unsigned char type; TYPE_5__ set_screen_power_mode; TYPE_4__ inject_text; TYPE_3__ inject_scroll_event; TYPE_2__ inject_mouse_event; TYPE_1__ inject_keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG_CLIPBOARD_TEXT_MAX_LENGTH ; 
 int /*<<< orphan*/  CONTROL_MSG_TEXT_MAX_LENGTH ; 
#define  CONTROL_MSG_TYPE_BACK_OR_SCREEN_ON 137 
#define  CONTROL_MSG_TYPE_COLLAPSE_NOTIFICATION_PANEL 136 
#define  CONTROL_MSG_TYPE_EXPAND_NOTIFICATION_PANEL 135 
#define  CONTROL_MSG_TYPE_GET_CLIPBOARD 134 
#define  CONTROL_MSG_TYPE_INJECT_KEYCODE 133 
#define  CONTROL_MSG_TYPE_INJECT_MOUSE_EVENT 132 
#define  CONTROL_MSG_TYPE_INJECT_SCROLL_EVENT 131 
#define  CONTROL_MSG_TYPE_INJECT_TEXT 130 
#define  CONTROL_MSG_TYPE_SET_CLIPBOARD 129 
#define  CONTROL_MSG_TYPE_SET_SCREEN_POWER_MODE 128 
 int /*<<< orphan*/  LOGW (char*,unsigned int) ; 
 int /*<<< orphan*/  buffer_write32be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_position (unsigned char*,int /*<<< orphan*/ *) ; 
 size_t write_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

size_t
control_msg_serialize(const struct control_msg *msg, unsigned char *buf) {
    buf[0] = msg->type;
    switch (msg->type) {
        case CONTROL_MSG_TYPE_INJECT_KEYCODE:
            buf[1] = msg->inject_keycode.action;
            buffer_write32be(&buf[2], msg->inject_keycode.keycode);
            buffer_write32be(&buf[6], msg->inject_keycode.metastate);
            return 10;
        case CONTROL_MSG_TYPE_INJECT_TEXT: {
            size_t len = write_string(msg->inject_text.text,
                                      CONTROL_MSG_TEXT_MAX_LENGTH, &buf[1]);
            return 1 + len;
        }
        case CONTROL_MSG_TYPE_INJECT_MOUSE_EVENT:
            buf[1] = msg->inject_mouse_event.action;
            buffer_write32be(&buf[2], msg->inject_mouse_event.buttons);
            write_position(&buf[6], &msg->inject_mouse_event.position);
            return 18;
        case CONTROL_MSG_TYPE_INJECT_SCROLL_EVENT:
            write_position(&buf[1], &msg->inject_scroll_event.position);
            buffer_write32be(&buf[13],
                             (uint32_t) msg->inject_scroll_event.hscroll);
            buffer_write32be(&buf[17],
                             (uint32_t) msg->inject_scroll_event.vscroll);
            return 21;
        case CONTROL_MSG_TYPE_SET_CLIPBOARD: {
            size_t len = write_string(msg->inject_text.text,
                                      CONTROL_MSG_CLIPBOARD_TEXT_MAX_LENGTH,
                                      &buf[1]);
            return 1 + len;
        }
        case CONTROL_MSG_TYPE_SET_SCREEN_POWER_MODE:
            buf[1] = msg->set_screen_power_mode.mode;
            return 2;
        case CONTROL_MSG_TYPE_BACK_OR_SCREEN_ON:
        case CONTROL_MSG_TYPE_EXPAND_NOTIFICATION_PANEL:
        case CONTROL_MSG_TYPE_COLLAPSE_NOTIFICATION_PANEL:
        case CONTROL_MSG_TYPE_GET_CLIPBOARD:
            // no additional data
            return 1;
        default:
            LOGW("Unknown message type: %u", (unsigned) msg->type);
            return 0;
    }
}