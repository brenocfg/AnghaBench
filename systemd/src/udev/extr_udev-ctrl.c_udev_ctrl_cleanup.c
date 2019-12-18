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
struct TYPE_2__ {int /*<<< orphan*/  un; } ;
struct udev_ctrl {TYPE_1__ saddr; scalar_t__ cleanup_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  sockaddr_un_unlink (int /*<<< orphan*/ *) ; 

int udev_ctrl_cleanup(struct udev_ctrl *uctrl) {
        if (!uctrl)
                return 0;
        if (uctrl->cleanup_socket)
                sockaddr_un_unlink(&uctrl->saddr.un);
        return 0;
}