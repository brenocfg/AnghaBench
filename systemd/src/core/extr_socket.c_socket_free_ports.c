#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* ports; } ;
struct TYPE_9__ {struct TYPE_9__* path; int /*<<< orphan*/  fd; int /*<<< orphan*/  event_source; } ;
typedef  TYPE_1__ SocketPort ;
typedef  TYPE_2__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_cleanup_fd_list (TYPE_1__*) ; 

void socket_free_ports(Socket *s) {
        SocketPort *p;

        assert(s);

        while ((p = s->ports)) {
                LIST_REMOVE(port, s->ports, p);

                sd_event_source_unref(p->event_source);

                socket_cleanup_fd_list(p);
                safe_close(p->fd);
                free(p->path);
                free(p);
        }
}