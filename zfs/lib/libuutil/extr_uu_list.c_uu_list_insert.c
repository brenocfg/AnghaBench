#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * uln_prev; } ;
struct TYPE_9__ {scalar_t__ ul_debug; TYPE_2__ ul_null_node; } ;
typedef  TYPE_1__ uu_list_t ;
typedef  TYPE_2__ uu_list_node_impl_t ;
typedef  scalar_t__ uu_list_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELEM_TO_NODE (TYPE_1__*,void*) ; 
 scalar_t__ INDEX_CHECK (scalar_t__) ; 
 TYPE_2__* INDEX_TO_NODE (scalar_t__) ; 
 int /*<<< orphan*/  INDEX_VALID (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  list_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*,void*,...) ; 

void
uu_list_insert(uu_list_t *lp, void *elem, uu_list_index_t idx)
{
	uu_list_node_impl_t *np;

	np = INDEX_TO_NODE(idx);
	if (np == NULL)
		np = &lp->ul_null_node;

	if (lp->ul_debug) {
		if (!INDEX_VALID(lp, idx))
			uu_panic("uu_list_insert(%p, %p, %p): %s\n",
			    (void *)lp, elem, (void *)idx,
			    INDEX_CHECK(idx)? "outdated index" :
			    "invalid index");
		if (np->uln_prev == NULL)
			uu_panic("uu_list_insert(%p, %p, %p): out-of-date "
			    "index\n", (void *)lp, elem, (void *)idx);
	}

	list_insert(lp, ELEM_TO_NODE(lp, elem), np->uln_prev, np);
}