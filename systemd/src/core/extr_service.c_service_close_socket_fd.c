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
struct TYPE_4__ {int /*<<< orphan*/  accept_socket; int /*<<< orphan*/  socket_fd; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  asynchronous_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_ref_unset (int /*<<< orphan*/ *) ; 

void service_close_socket_fd(Service *s) {
        assert(s);

        /* Undo the effect of service_set_socket_fd(). */

        s->socket_fd = asynchronous_close(s->socket_fd);

        if (UNIT_ISSET(s->accept_socket)) {
                socket_connection_unref(SOCKET(UNIT_DEREF(s->accept_socket)));
                unit_ref_unset(&s->accept_socket);
        }
}