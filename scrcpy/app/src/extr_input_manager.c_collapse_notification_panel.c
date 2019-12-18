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
struct controller {int dummy; } ;
struct control_msg {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG_TYPE_COLLAPSE_NOTIFICATION_PANEL ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_msg (struct controller*,struct control_msg*) ; 

__attribute__((used)) static void
collapse_notification_panel(struct controller *controller) {
    struct control_msg msg;
    msg.type = CONTROL_MSG_TYPE_COLLAPSE_NOTIFICATION_PANEL;

    if (!controller_push_msg(controller, &msg)) {
        LOGW("Could not request 'collapse notification panel'");
    }
}