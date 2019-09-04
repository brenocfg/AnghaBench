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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_4__ {int /*<<< orphan*/  j_state_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int __log_start_commit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 

int log_start_commit(journal_t *journal, tid_t tid)
{
    int ret;

    jbd_lock(&journal->j_state_lock);
    ret = __log_start_commit(journal, tid);
    jbd_unlock(&journal->j_state_lock);
    return ret;
}