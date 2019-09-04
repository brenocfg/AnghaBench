#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_3__ {int /*<<< orphan*/  j_wait_commit; int /*<<< orphan*/  j_commit_sequence; int /*<<< orphan*/  j_commit_request; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_geq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int __log_start_commit(journal_t *journal, tid_t target)
{
    /*
     * Are we already doing a recent enough commit?
     */
    if (!tid_geq(journal->j_commit_request, target)) {
        /*
         * We want a new commit: OK, mark the request and wakup the
         * commit thread.  We do _not_ do the commit ourselves.
         */

        journal->j_commit_request = target;
        jbd_debug(1, "JBD: requesting commit %d/%d\n",
                  journal->j_commit_request,
                  journal->j_commit_sequence);
        wake_up(&journal->j_wait_commit);
        return 1;
    }
    return 0;
}