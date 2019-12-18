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
struct TYPE_4__ {int /*<<< orphan*/  an_state; struct TYPE_4__* an_next; struct TYPE_4__* an_prev; } ;
typedef  TYPE_1__ kcf_areq_node_t ;
struct TYPE_5__ {TYPE_1__* gs_first; TYPE_1__* gs_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_CANCELED ; 
 TYPE_3__* gswq ; 

void
kcf_remove_node(kcf_areq_node_t *node)
{
	kcf_areq_node_t *nextp = node->an_next;
	kcf_areq_node_t *prevp = node->an_prev;

	if (nextp != NULL)
		nextp->an_prev = prevp;
	else
		gswq->gs_last = prevp;

	if (prevp != NULL)
		prevp->an_next = nextp;
	else
		gswq->gs_first = nextp;

	node->an_state = REQ_CANCELED;
}