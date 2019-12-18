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
struct msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct msg* TAILQ_NEXT (struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_msgq ; 
 int /*<<< orphan*/  m_tqe ; 
 int /*<<< orphan*/  msg_free (struct msg*) ; 
 scalar_t__ nfree_msgq ; 

void
msg_deinit(void)
{
    struct msg *msg, *nmsg;

    for (msg = TAILQ_FIRST(&free_msgq); msg != NULL;
         msg = nmsg, nfree_msgq--) {
        ASSERT(nfree_msgq > 0);
        nmsg = TAILQ_NEXT(msg, m_tqe);
        msg_free(msg);
    }
    ASSERT(nfree_msgq == 0);
}