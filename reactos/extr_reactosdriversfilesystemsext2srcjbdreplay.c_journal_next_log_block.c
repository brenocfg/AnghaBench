#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int j_free; unsigned long j_head; unsigned long j_last; unsigned long j_first; int /*<<< orphan*/  j_state_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 
 int journal_bmap (TYPE_1__*,unsigned long,unsigned long*) ; 

int journal_next_log_block(journal_t *journal, unsigned long *retp)
{
    unsigned long blocknr;

    jbd_lock(&journal->j_state_lock);
    J_ASSERT(journal->j_free > 1);

    blocknr = journal->j_head;
    journal->j_head++;
    journal->j_free--;
    if (journal->j_head == journal->j_last)
        journal->j_head = journal->j_first;
    jbd_unlock(&journal->j_state_lock);
    return journal_bmap(journal, blocknr, retp);
}