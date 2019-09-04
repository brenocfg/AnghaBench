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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ frag_id ; 
 int /*<<< orphan*/  free_msgq ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ msg_id ; 
 scalar_t__ nfree_msgq ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmo_rbs ; 
 int /*<<< orphan*/  tmo_rbt ; 

void
msg_init(void)
{
    log_debug(LOG_DEBUG, "msg size %d", sizeof(struct msg));
    msg_id = 0;
    frag_id = 0;
    nfree_msgq = 0;
    TAILQ_INIT(&free_msgq);
    rbtree_init(&tmo_rbt, &tmo_rbs);
}