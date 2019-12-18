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
struct TYPE_3__ {int sn_rv; int /*<<< orphan*/  sn_lock; int /*<<< orphan*/  sn_cv; int /*<<< orphan*/  sn_state; } ;
typedef  TYPE_1__ kcf_sreq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_DONE ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
kcf_sop_done(kcf_sreq_node_t *sreq, int error)
{
	mutex_enter(&sreq->sn_lock);
	sreq->sn_state = REQ_DONE;
	sreq->sn_rv = error;
	cv_signal(&sreq->sn_cv);
	mutex_exit(&sreq->sn_lock);
}