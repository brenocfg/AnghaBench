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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {unsigned char action; } ;
struct TYPE_9__ {int /*<<< orphan*/  vscroll; int /*<<< orphan*/  hscroll; int /*<<< orphan*/  position; } ;
struct TYPE_8__ {unsigned char action; int /*<<< orphan*/  position; int /*<<< orphan*/  buttons; } ;
struct TYPE_7__ {int /*<<< orphan*/  text; } ;
struct TYPE_6__ {unsigned char action; int /*<<< orphan*/  metastate; int /*<<< orphan*/  keycode; } ;
struct control_event {unsigned char type; TYPE_5__ command_event; TYPE_4__ scroll_event; TYPE_3__ mouse_event; TYPE_2__ text_event; TYPE_1__ keycode_event; } ;

/* Variables and functions */
#define  CONTROL_EVENT_TYPE_COMMAND 132 
#define  CONTROL_EVENT_TYPE_KEYCODE 131 
#define  CONTROL_EVENT_TYPE_MOUSE 130 
#define  CONTROL_EVENT_TYPE_SCROLL 129 
#define  CONTROL_EVENT_TYPE_TEXT 128 
 int /*<<< orphan*/  LOGW (char*,unsigned int) ; 
 size_t TEXT_MAX_LENGTH ; 
 int /*<<< orphan*/  buffer_write16be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_write32be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_position (unsigned char*,int /*<<< orphan*/ *) ; 

int
control_event_serialize(const struct control_event *event, unsigned char *buf) {
    buf[0] = event->type;
    switch (event->type) {
        case CONTROL_EVENT_TYPE_KEYCODE:
            buf[1] = event->keycode_event.action;
            buffer_write32be(&buf[2], event->keycode_event.keycode);
            buffer_write32be(&buf[6], event->keycode_event.metastate);
            return 10;
        case CONTROL_EVENT_TYPE_TEXT: {
            // write length (2 bytes) + string (non nul-terminated)
            size_t len = strlen(event->text_event.text);
            if (len > TEXT_MAX_LENGTH) {
                // injecting a text takes time, so limit the text length
                len = TEXT_MAX_LENGTH;
            }
            buffer_write16be(&buf[1], (uint16_t) len);
            memcpy(&buf[3], event->text_event.text, len);
            return 3 + len;
        }
        case CONTROL_EVENT_TYPE_MOUSE:
            buf[1] = event->mouse_event.action;
            buffer_write32be(&buf[2], event->mouse_event.buttons);
            write_position(&buf[6], &event->mouse_event.position);
            return 18;
        case CONTROL_EVENT_TYPE_SCROLL:
            write_position(&buf[1], &event->scroll_event.position);
            buffer_write32be(&buf[13], (uint32_t) event->scroll_event.hscroll);
            buffer_write32be(&buf[17], (uint32_t) event->scroll_event.vscroll);
            return 21;
        case CONTROL_EVENT_TYPE_COMMAND:
            buf[1] = event->command_event.action;
            return 2;
        default:
            LOGW("Unknown event type: %u", (unsigned) event->type);
            return 0;
    }
}