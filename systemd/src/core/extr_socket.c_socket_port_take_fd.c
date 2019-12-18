#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ SocketPort ;
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fdset_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_port_take_fd(SocketPort *p, FDSet *fds, int fd) {
        assert(p);

        safe_close(p->fd);
        p->fd = fdset_remove(fds, fd);
}