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
struct conn {int sd; scalar_t__ authenticated; scalar_t__ redis; scalar_t__ done; scalar_t__ eof; scalar_t__ connected; scalar_t__ connecting; scalar_t__ proxy; scalar_t__ client; scalar_t__ send_ready; scalar_t__ send_active; scalar_t__ recv_ready; scalar_t__ recv_active; scalar_t__ err; scalar_t__ events; scalar_t__ recv_bytes; scalar_t__ send_bytes; int /*<<< orphan*/ * smsg; int /*<<< orphan*/ * rmsg; int /*<<< orphan*/  omsg_q; int /*<<< orphan*/  imsg_q; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct conn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_tqe ; 
 int /*<<< orphan*/  free_connq ; 
 struct conn* nc_alloc (int) ; 
 int /*<<< orphan*/  ncurr_conn ; 
 scalar_t__ nfree_connq ; 
 int /*<<< orphan*/  ntotal_conn ; 

__attribute__((used)) static struct conn *
_conn_get(void)
{
    struct conn *conn;

    if (!TAILQ_EMPTY(&free_connq)) {
        ASSERT(nfree_connq > 0);

        conn = TAILQ_FIRST(&free_connq);
        nfree_connq--;
        TAILQ_REMOVE(&free_connq, conn, conn_tqe);
    } else {
        conn = nc_alloc(sizeof(*conn));
        if (conn == NULL) {
            return NULL;
        }
    }

    conn->owner = NULL;

    conn->sd = -1;
    /* {family, addrlen, addr} are initialized in enqueue handler */

    TAILQ_INIT(&conn->imsg_q);
    TAILQ_INIT(&conn->omsg_q);
    conn->rmsg = NULL;
    conn->smsg = NULL;

    /*
     * Callbacks {recv, recv_next, recv_done}, {send, send_next, send_done},
     * {close, active}, parse, {ref, unref}, {enqueue_inq, dequeue_inq} and
     * {enqueue_outq, dequeue_outq} are initialized by the wrapper.
     */

    conn->send_bytes = 0;
    conn->recv_bytes = 0;

    conn->events = 0;
    conn->err = 0;
    conn->recv_active = 0;
    conn->recv_ready = 0;
    conn->send_active = 0;
    conn->send_ready = 0;

    conn->client = 0;
    conn->proxy = 0;
    conn->connecting = 0;
    conn->connected = 0;
    conn->eof = 0;
    conn->done = 0;
    conn->redis = 0;
    conn->authenticated = 0;

    ntotal_conn++;
    ncurr_conn++;

    return conn;
}