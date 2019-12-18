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
struct conn {scalar_t__ sd; scalar_t__ client; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_tqe ; 
 int /*<<< orphan*/  free_connq ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conn*) ; 
 int /*<<< orphan*/  ncurr_cconn ; 
 int /*<<< orphan*/  ncurr_conn ; 
 int /*<<< orphan*/  nfree_connq ; 

void
conn_put(struct conn *conn)
{
    ASSERT(conn->sd < 0);
    ASSERT(conn->owner == NULL);

    log_debug(LOG_VVERB, "put conn %p", conn);

    nfree_connq++;
    TAILQ_INSERT_HEAD(&free_connq, conn, conn_tqe);

    if (conn->client) {
        ncurr_cconn--;
    }
    ncurr_conn--;
}