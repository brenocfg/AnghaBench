#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  an_state; struct TYPE_4__* an_prev; struct TYPE_4__* an_next; } ;
typedef  TYPE_1__ kcf_areq_node_t ;
struct TYPE_5__ {scalar_t__ gs_njobs; scalar_t__ gs_maxjobs; int /*<<< orphan*/  gs_lock; TYPE_1__* gs_last; TYPE_1__* gs_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CRYPTO_BUSY ; 
 int /*<<< orphan*/  REQ_WAITING ; 
 TYPE_3__* gswq ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kcf_enqueue(kcf_areq_node_t *node)
{
	kcf_areq_node_t *tnode;

	mutex_enter(&gswq->gs_lock);

	if (gswq->gs_njobs >= gswq->gs_maxjobs) {
		mutex_exit(&gswq->gs_lock);
		return (CRYPTO_BUSY);
	}

	if (gswq->gs_last == NULL) {
		gswq->gs_first = gswq->gs_last = node;
	} else {
		ASSERT(gswq->gs_last->an_next == NULL);
		tnode = gswq->gs_last;
		tnode->an_next = node;
		gswq->gs_last = node;
		node->an_prev = tnode;
	}

	gswq->gs_njobs++;

	/* an_lock not needed here as we hold gs_lock */
	node->an_state = REQ_WAITING;

	mutex_exit(&gswq->gs_lock);

	return (0);
}