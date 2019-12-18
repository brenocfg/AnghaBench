#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  fdname; int /*<<< orphan*/  fd; int /*<<< orphan*/  service; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ ServiceFDStore ;

/* Variables and functions */
 int EPOLLERR ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_fd_store_unlink (TYPE_1__*) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_fd_store_io(sd_event_source *e, int fd, uint32_t revents, void *userdata) {
        ServiceFDStore *fs = userdata;

        assert(e);
        assert(fs);

        /* If we get either EPOLLHUP or EPOLLERR, it's time to remove this entry from the fd store */
        log_unit_debug(UNIT(fs->service),
                       "Received %s on stored fd %d (%s), closing.",
                       revents & EPOLLERR ? "EPOLLERR" : "EPOLLHUP",
                       fs->fd, strna(fs->fdname));
        service_fd_store_unlink(fs);
        return 0;
}