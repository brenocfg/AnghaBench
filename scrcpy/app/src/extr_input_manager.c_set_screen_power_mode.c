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
struct TYPE_2__ {int mode; } ;
struct control_msg {TYPE_1__ set_screen_power_mode; int /*<<< orphan*/  type; } ;
typedef  enum screen_power_mode { ____Placeholder_screen_power_mode } screen_power_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG_TYPE_SET_SCREEN_POWER_MODE ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_msg (struct controller*,struct control_msg*) ; 

__attribute__((used)) static void
set_screen_power_mode(struct controller *controller,
                      enum screen_power_mode mode) {
    struct control_msg msg;
    msg.type = CONTROL_MSG_TYPE_SET_SCREEN_POWER_MODE;
    msg.set_screen_power_mode.mode = mode;

    if (!controller_push_msg(controller, &msg)) {
        LOGW("Could not request 'set screen power mode'");
    }
}