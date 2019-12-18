#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  text; } ;
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
struct control_msg {int type; TYPE_2__ set_clipboard; TYPE_1__ inject_text; } ;

/* Variables and functions */
#define  CONTROL_MSG_TYPE_INJECT_TEXT 129 
#define  CONTROL_MSG_TYPE_SET_CLIPBOARD 128 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 

void
control_msg_destroy(struct control_msg *msg) {
    switch (msg->type) {
        case CONTROL_MSG_TYPE_INJECT_TEXT:
            SDL_free(msg->inject_text.text);
            break;
        case CONTROL_MSG_TYPE_SET_CLIPBOARD:
            SDL_free(msg->set_clipboard.text);
            break;
        default:
            // do nothing
            break;
    }
}