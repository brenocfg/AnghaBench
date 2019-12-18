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
struct udev_ctrl {int /*<<< orphan*/  event_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_ON ; 
 int /*<<< orphan*/  sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_ctrl_disconnect (struct udev_ctrl*) ; 
 int /*<<< orphan*/  udev_ctrl_unref (struct udev_ctrl*) ; 

__attribute__((used)) static void udev_ctrl_disconnect_and_listen_again(struct udev_ctrl *uctrl) {
        udev_ctrl_disconnect(uctrl);
        udev_ctrl_unref(uctrl);
        (void) sd_event_source_set_enabled(uctrl->event_source, SD_EVENT_ON);
}