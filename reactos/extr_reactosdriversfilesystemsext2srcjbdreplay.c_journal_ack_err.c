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
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; scalar_t__ j_errno; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  JFS_ACK_ERR ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 

void journal_ack_err(journal_t *journal)
{
    jbd_lock(&journal->j_state_lock);
    if (journal->j_errno)
        journal->j_flags |= JFS_ACK_ERR;
    jbd_unlock(&journal->j_state_lock);
}