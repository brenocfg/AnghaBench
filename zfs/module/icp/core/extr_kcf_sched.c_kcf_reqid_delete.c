#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rt_lock; TYPE_2__** rt_idhash; } ;
typedef  TYPE_1__ kcf_reqid_table_t ;
struct TYPE_8__ {int /*<<< orphan*/  an_done; struct TYPE_8__* an_idnext; struct TYPE_8__* an_idprev; } ;
typedef  TYPE_2__ kcf_areq_node_t ;
typedef  size_t crypto_req_id_t ;

/* Variables and functions */
 size_t GET_REQID (TYPE_2__*) ; 
 int REQID_HASH (size_t) ; 
 size_t REQID_TABLE_MASK ; 
 int /*<<< orphan*/  SET_REQID (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 TYPE_1__** kcf_reqid_table ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kcf_reqid_delete(kcf_areq_node_t *areq)
{
	int indx;
	kcf_areq_node_t *nextp, *prevp;
	crypto_req_id_t id = GET_REQID(areq);
	kcf_reqid_table_t *rt;

	rt = kcf_reqid_table[id & REQID_TABLE_MASK];
	indx = REQID_HASH(id);

	mutex_enter(&rt->rt_lock);

	nextp = areq->an_idnext;
	prevp = areq->an_idprev;
	if (nextp != NULL)
		nextp->an_idprev = prevp;
	if (prevp != NULL)
		prevp->an_idnext = nextp;
	else
		rt->rt_idhash[indx] = nextp;

	SET_REQID(areq, 0);
	cv_broadcast(&areq->an_done);

	mutex_exit(&rt->rt_lock);
}