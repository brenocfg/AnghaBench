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
typedef  int /*<<< orphan*/  udev_ctrl_handler_t ;
struct udev_ctrl {int /*<<< orphan*/  event_source; int /*<<< orphan*/  sock; int /*<<< orphan*/  event; void* userdata; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  assert (struct udev_ctrl*) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udev_ctrl*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 
 int udev_ctrl_attach_event (struct udev_ctrl*,int /*<<< orphan*/ *) ; 
 int udev_ctrl_enable_receiving (struct udev_ctrl*) ; 
 int /*<<< orphan*/  udev_ctrl_event_handler ; 

int udev_ctrl_start(struct udev_ctrl *uctrl, udev_ctrl_handler_t callback, void *userdata) {
        int r;

        assert(uctrl);

        if (!uctrl->event) {
                r = udev_ctrl_attach_event(uctrl, NULL);
                if (r < 0)
                        return r;
        }

        r = udev_ctrl_enable_receiving(uctrl);
        if (r < 0)
                return r;

        uctrl->callback = callback;
        uctrl->userdata = userdata;

        r = sd_event_add_io(uctrl->event, &uctrl->event_source, uctrl->sock, EPOLLIN, udev_ctrl_event_handler, uctrl);
        if (r < 0)
                return r;

        (void) sd_event_source_set_description(uctrl->event_source, "udev-ctrl");

        return 0;
}