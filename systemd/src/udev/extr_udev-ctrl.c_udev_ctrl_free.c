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
struct udev_ctrl {int /*<<< orphan*/  event; int /*<<< orphan*/  sock; int /*<<< orphan*/  event_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udev_ctrl*) ; 
 struct udev_ctrl* mfree (struct udev_ctrl*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_ctrl_disconnect (struct udev_ctrl*) ; 

__attribute__((used)) static struct udev_ctrl *udev_ctrl_free(struct udev_ctrl *uctrl) {
        assert(uctrl);

        udev_ctrl_disconnect(uctrl);

        sd_event_source_unref(uctrl->event_source);
        safe_close(uctrl->sock);

        sd_event_unref(uctrl->event);
        return mfree(uctrl);
}