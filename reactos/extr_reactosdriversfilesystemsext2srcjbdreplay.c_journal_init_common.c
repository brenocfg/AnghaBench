#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int j_commit_interval; int /*<<< orphan*/  j_flags; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_revoke_lock; int /*<<< orphan*/  j_checkpoint_mutex; int /*<<< orphan*/  j_barrier; int /*<<< orphan*/  j_wait_updates; int /*<<< orphan*/  j_wait_commit; int /*<<< orphan*/  j_wait_checkpoint; int /*<<< orphan*/  j_wait_done_commit; int /*<<< orphan*/  j_wait_logspace; int /*<<< orphan*/  j_wait_transaction_locked; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int JBD_DEFAULT_MAX_COMMIT_AGE ; 
 int /*<<< orphan*/  JFS_ABORT ; 
 int /*<<< orphan*/  JOURNAL_REVOKE_DEFAULT_HASH ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_lock_init (int /*<<< orphan*/ *) ; 
 int journal_init_revoke (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static journal_t * journal_init_common (void)
{
    journal_t *journal;
    int err;

    journal = kzalloc(sizeof(*journal), GFP_KERNEL);
    if (!journal)
        goto fail;

    init_waitqueue_head(&journal->j_wait_transaction_locked);
    init_waitqueue_head(&journal->j_wait_logspace);
    init_waitqueue_head(&journal->j_wait_done_commit);
    init_waitqueue_head(&journal->j_wait_checkpoint);
    init_waitqueue_head(&journal->j_wait_commit);
    init_waitqueue_head(&journal->j_wait_updates);
    mutex_init(&journal->j_barrier);
    mutex_init(&journal->j_checkpoint_mutex);
    jbd_lock_init(&journal->j_revoke_lock);
    jbd_lock_init(&journal->j_list_lock);
    jbd_lock_init(&journal->j_state_lock);

    journal->j_commit_interval = (HZ * JBD_DEFAULT_MAX_COMMIT_AGE);

    /* The journal is marked for error until we succeed with recovery! */
    journal->j_flags = JFS_ABORT;

    /* Set up a default-sized revoke table for the new mount. */
    err = journal_init_revoke(journal, JOURNAL_REVOKE_DEFAULT_HASH);
    if (err) {
        kfree(journal);
        goto fail;
    }
    return journal;
fail:
    return NULL;
}