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
struct TYPE_2__ {int /*<<< orphan*/  sa; int /*<<< orphan*/  un; } ;
struct udev_ctrl {int bound; int cleanup_socket; int /*<<< orphan*/  sock; int /*<<< orphan*/  addrlen; TYPE_1__ saddr; } ;

/* Variables and functions */
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  assert (struct udev_ctrl*) ; 
 int bind (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_error_errno (scalar_t__,char*) ; 
 int /*<<< orphan*/  sockaddr_un_unlink (int /*<<< orphan*/ *) ; 

int udev_ctrl_enable_receiving(struct udev_ctrl *uctrl) {
        int r;

        assert(uctrl);

        if (uctrl->bound)
                return 0;

        r = bind(uctrl->sock, &uctrl->saddr.sa, uctrl->addrlen);
        if (r < 0 && errno == EADDRINUSE) {
                (void) sockaddr_un_unlink(&uctrl->saddr.un);
                r = bind(uctrl->sock, &uctrl->saddr.sa, uctrl->addrlen);
        }

        if (r < 0)
                return log_error_errno(errno, "Failed to bind udev control socket: %m");

        if (listen(uctrl->sock, 0) < 0)
                return log_error_errno(errno, "Failed to listen udev control socket: %m");

        uctrl->bound = true;
        uctrl->cleanup_socket = true;

        return 0;
}