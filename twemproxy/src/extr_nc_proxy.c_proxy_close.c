#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct context {int dummy; } ;
struct conn {int sd; int /*<<< orphan*/  (* unref ) (struct conn*) ;int /*<<< orphan*/  omsg_q; int /*<<< orphan*/  imsg_q; int /*<<< orphan*/ * smsg; int /*<<< orphan*/ * rmsg; scalar_t__ proxy; int /*<<< orphan*/  client; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  conn_put (struct conn*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct conn*) ; 
 int /*<<< orphan*/  stub2 (struct conn*) ; 

void
proxy_close(struct context *ctx, struct conn *conn)
{
    rstatus_t status;

    ASSERT(!conn->client && conn->proxy);

    if (conn->sd < 0) {
        conn->unref(conn);
        conn_put(conn);
        return;
    }

    ASSERT(conn->rmsg == NULL);
    ASSERT(conn->smsg == NULL);
    ASSERT(TAILQ_EMPTY(&conn->imsg_q));
    ASSERT(TAILQ_EMPTY(&conn->omsg_q));

    conn->unref(conn);

    status = close(conn->sd);
    if (status < 0) {
        log_error("close p %d failed, ignored: %s", conn->sd, strerror(errno));
    }
    conn->sd = -1;

    conn_put(conn);
}