#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct aeEventLoop {int dummy; } ;
struct TYPE_5__ {scalar_t__ state; int flags; int /*<<< orphan*/ * read_handler; int /*<<< orphan*/ * write_handler; int /*<<< orphan*/ * conn_handler; int /*<<< orphan*/  fd; int /*<<< orphan*/  last_errno; } ;
typedef  TYPE_1__ connection ;
struct TYPE_6__ {int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int CONN_FLAG_WRITE_BARRIER ; 
 scalar_t__ CONN_STATE_CONNECTED ; 
 scalar_t__ CONN_STATE_CONNECTING ; 
 scalar_t__ CONN_STATE_ERROR ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callHandler (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ connGetSocketError (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__ server ; 

__attribute__((used)) static void connSocketEventHandler(struct aeEventLoop *el, int fd, void *clientData, int mask)
{
    UNUSED(el);
    UNUSED(fd);
    connection *conn = clientData;

    if (conn->state == CONN_STATE_CONNECTING &&
            (mask & AE_WRITABLE) && conn->conn_handler) {

        if (connGetSocketError(conn)) {
            conn->last_errno = errno;
            conn->state = CONN_STATE_ERROR;
        } else {
            conn->state = CONN_STATE_CONNECTED;
        }

        if (!conn->write_handler) aeDeleteFileEvent(server.el,conn->fd,AE_WRITABLE);

        if (!callHandler(conn, conn->conn_handler)) return;
        conn->conn_handler = NULL;
    }

    /* Normally we execute the readable event first, and the writable
     * event later. This is useful as sometimes we may be able
     * to serve the reply of a query immediately after processing the
     * query.
     *
     * However if WRITE_BARRIER is set in the mask, our application is
     * asking us to do the reverse: never fire the writable event
     * after the readable. In such a case, we invert the calls.
     * This is useful when, for instance, we want to do things
     * in the beforeSleep() hook, like fsync'ing a file to disk,
     * before replying to a client. */
    int invert = conn->flags & CONN_FLAG_WRITE_BARRIER;

    int call_write = (mask & AE_WRITABLE) && conn->write_handler;
    int call_read = (mask & AE_READABLE) && conn->read_handler;

    /* Handle normal I/O flows */
    if (!invert && call_read) {
        if (!callHandler(conn, conn->read_handler)) return;
    }
    /* Fire the writable event. */
    if (call_write) {
        if (!callHandler(conn, conn->write_handler)) return;
    }
    /* If we have to invert the call, fire the readable event now
     * after the writable one. */
    if (invert && call_read) {
        if (!callHandler(conn, conn->read_handler)) return;
    }
}