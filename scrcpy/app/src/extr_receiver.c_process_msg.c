#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct receiver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;
struct device_msg {int type; TYPE_1__ clipboard; } ;

/* Variables and functions */
#define  DEVICE_MSG_TYPE_CLIPBOARD 128 
 int /*<<< orphan*/  LOGI (char*) ; 
 int /*<<< orphan*/  SDL_SetClipboardText (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_msg(struct receiver *receiver, struct device_msg *msg) {
    switch (msg->type) {
        case DEVICE_MSG_TYPE_CLIPBOARD:
            LOGI("Device clipboard copied");
            SDL_SetClipboardText(msg->clipboard.text);
            break;
    }
}