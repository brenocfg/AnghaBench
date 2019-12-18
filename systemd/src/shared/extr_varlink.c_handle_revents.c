#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int connecting; int got_pollhup; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_SET (int,int) ; 
 int POLLHUP ; 
 int POLLOUT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_log (TYPE_1__*,char*) ; 

__attribute__((used)) static void handle_revents(Varlink *v, int revents) {
        assert(v);

        if (v->connecting) {
                /* If we have seen POLLOUT or POLLHUP on a socket we are asynchronously waiting a connect()
                 * to complete on, we know we are ready. We don't read the connection error here though,
                 * we'll get the error on the next read() or write(). */
                if ((revents & (POLLOUT|POLLHUP)) == 0)
                        return;

                varlink_log(v, "Anynchronous connection completed.");
                v->connecting = false;
        } else {
                /* Note that we don't care much about POLLIN/POLLOUT here, we'll just try reading and writing
                 * what we can. However, we do care about POLLHUP to detect connection termination even if we
                 * momentarily don't want to read nor write anything. */

                if (!FLAGS_SET(revents, POLLHUP))
                        return;

                varlink_log(v, "Got POLLHUP from socket.");
                v->got_pollhup = true;
        }
}