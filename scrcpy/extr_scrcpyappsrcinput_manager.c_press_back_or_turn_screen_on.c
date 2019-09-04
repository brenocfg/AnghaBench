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
struct TYPE_2__ {int /*<<< orphan*/  action; } ;
struct control_event {TYPE_1__ command_event; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_EVENT_COMMAND_BACK_OR_SCREEN_ON ; 
 int /*<<< orphan*/  CONTROL_EVENT_TYPE_COMMAND ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_event (struct controller*,struct control_event*) ; 

__attribute__((used)) static void
press_back_or_turn_screen_on(struct controller *controller) {
    struct control_event control_event;
    control_event.type = CONTROL_EVENT_TYPE_COMMAND;
    control_event.command_event.action =
            CONTROL_EVENT_COMMAND_BACK_OR_SCREEN_ON;

    if (!controller_push_event(controller, &control_event)) {
        LOGW("Cannot turn screen on");
    }
}