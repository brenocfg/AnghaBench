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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct mbuf* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mbufq ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_remove (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ nfree_mbufq ; 

void
mbuf_deinit(void)
{
    while (!STAILQ_EMPTY(&free_mbufq)) {
        struct mbuf *mbuf = STAILQ_FIRST(&free_mbufq);
        mbuf_remove(&free_mbufq, mbuf);
        mbuf_free(mbuf);
        nfree_mbufq--;
    }
    ASSERT(nfree_mbufq == 0);
}