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
struct TYPE_2__ {scalar_t__ ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  Server ;
typedef  int /*<<< orphan*/  Fifo ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int EPOLLIN ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ *) ; 
 int fifo_process (int /*<<< orphan*/ *) ; 
 int log_info_errno (int,char*) ; 

__attribute__((used)) static int process_event(Server *s, struct epoll_event *ev) {
        int r;
        Fifo *f;

        assert(s);

        if (!(ev->events & EPOLLIN))
                return log_info_errno(SYNTHETIC_ERRNO(EIO),
                                      "Got invalid event from epoll. (3)");

        f = (Fifo*) ev->data.ptr;
        r = fifo_process(f);
        if (r < 0) {
                log_info_errno(r, "Got error on fifo: %m");
                fifo_free(f);
                return r;
        }

        return 0;
}