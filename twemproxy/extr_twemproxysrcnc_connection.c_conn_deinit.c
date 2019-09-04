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
struct conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct conn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct conn* TAILQ_NEXT (struct conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_free (struct conn*) ; 
 int /*<<< orphan*/  conn_tqe ; 
 int /*<<< orphan*/  free_connq ; 
 scalar_t__ nfree_connq ; 

void
conn_deinit(void)
{
    struct conn *conn, *nconn; /* current and next connection */

    for (conn = TAILQ_FIRST(&free_connq); conn != NULL;
         conn = nconn, nfree_connq--) {
        ASSERT(nfree_connq > 0);
        nconn = TAILQ_NEXT(conn, conn_tqe);
        conn_free(conn);
    }
    ASSERT(nfree_connq == 0);
}