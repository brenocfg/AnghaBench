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
struct udev_ctrl {int /*<<< orphan*/  sock_connect; int /*<<< orphan*/  event_source_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udev_ctrl_disconnect(struct udev_ctrl *uctrl) {
        if (!uctrl)
                return;

        uctrl->event_source_connect = sd_event_source_unref(uctrl->event_source_connect);
        uctrl->sock_connect = safe_close(uctrl->sock_connect);
}