#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ sa_family; } ;
struct TYPE_16__ {TYPE_1__ sa; } ;
struct TYPE_17__ {scalar_t__ nspid; int last_connect_error; TYPE_2__ sockaddr; scalar_t__ machine; scalar_t__ exec_path; } ;
typedef  TYPE_3__ sd_bus ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int ECONNREFUSED ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int bus_attach_inotify_event (TYPE_3__*) ; 
 int bus_attach_io_events (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_close_inotify_fd (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_close_io_fds (TYPE_3__*) ; 
 int bus_container_connect_socket (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_kill_exec (TYPE_3__*) ; 
 int bus_parse_next_address (TYPE_3__*) ; 
 int bus_socket_connect (TYPE_3__*) ; 
 int bus_socket_exec (TYPE_3__*) ; 

__attribute__((used)) static int bus_start_address(sd_bus *b) {
        int r;

        assert(b);

        for (;;) {
                bus_close_io_fds(b);
                bus_close_inotify_fd(b);

                bus_kill_exec(b);

                /* If you provide multiple different bus-addresses, we
                 * try all of them in order and use the first one that
                 * succeeds. */

                if (b->exec_path)
                        r = bus_socket_exec(b);
                else if ((b->nspid > 0 || b->machine) && b->sockaddr.sa.sa_family != AF_UNSPEC)
                        r = bus_container_connect_socket(b);
                else if (b->sockaddr.sa.sa_family != AF_UNSPEC)
                        r = bus_socket_connect(b);
                else
                        goto next;

                if (r >= 0) {
                        int q;

                        q = bus_attach_io_events(b);
                        if (q < 0)
                                return q;

                        q = bus_attach_inotify_event(b);
                        if (q < 0)
                                return q;

                        return r;
                }

                b->last_connect_error = -r;

        next:
                r = bus_parse_next_address(b);
                if (r < 0)
                        return r;
                if (r == 0)
                        return b->last_connect_error > 0 ? -b->last_connect_error : -ECONNREFUSED;
        }
}