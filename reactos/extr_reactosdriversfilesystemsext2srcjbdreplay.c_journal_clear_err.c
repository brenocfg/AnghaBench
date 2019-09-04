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
struct TYPE_3__ {int j_flags; int /*<<< orphan*/  j_state_lock; scalar_t__ j_errno; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EROFS ; 
 int JFS_ABORT ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 

int journal_clear_err(journal_t *journal)
{
    int err = 0;

    jbd_lock(&journal->j_state_lock);
    if (journal->j_flags & JFS_ABORT)
        err = -EROFS;
    else
        journal->j_errno = 0;
    jbd_unlock(&journal->j_state_lock);
    return err;
}