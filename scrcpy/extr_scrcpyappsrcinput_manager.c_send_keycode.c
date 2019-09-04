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
struct controller {int dummy; } ;
struct TYPE_2__ {int keycode; int /*<<< orphan*/  action; scalar_t__ metastate; } ;
struct control_event {TYPE_1__ keycode_event; int /*<<< orphan*/  type; } ;
typedef  enum android_keycode { ____Placeholder_android_keycode } android_keycode ;

/* Variables and functions */
 int ACTION_DOWN ; 
 int ACTION_UP ; 
 int /*<<< orphan*/  AKEY_EVENT_ACTION_DOWN ; 
 int /*<<< orphan*/  AKEY_EVENT_ACTION_UP ; 
 int /*<<< orphan*/  CONTROL_EVENT_TYPE_KEYCODE ; 
 int /*<<< orphan*/  LOGW (char*,char const*) ; 
 int /*<<< orphan*/  controller_push_event (struct controller*,struct control_event*) ; 

__attribute__((used)) static void
send_keycode(struct controller *controller, enum android_keycode keycode,
             int actions, const char *name) {
    // send DOWN event
    struct control_event control_event;
    control_event.type = CONTROL_EVENT_TYPE_KEYCODE;
    control_event.keycode_event.keycode = keycode;
    control_event.keycode_event.metastate = 0;

    if (actions & ACTION_DOWN) {
        control_event.keycode_event.action = AKEY_EVENT_ACTION_DOWN;
        if (!controller_push_event(controller, &control_event)) {
            LOGW("Cannot send %s (DOWN)", name);
            return;
        }
    }

    if (actions & ACTION_UP) {
        control_event.keycode_event.action = AKEY_EVENT_ACTION_UP;
        if (!controller_push_event(controller, &control_event)) {
            LOGW("Cannot send %s (UP)", name);
        }
    }
}