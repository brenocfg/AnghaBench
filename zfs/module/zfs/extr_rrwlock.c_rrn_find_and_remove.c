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
struct TYPE_7__ {int /*<<< orphan*/  rr_linked_rcount; } ;
typedef  TYPE_1__ rrwlock_t ;
struct TYPE_8__ {void* rn_tag; struct TYPE_8__* rn_next; TYPE_1__* rn_rrl; } ;
typedef  TYPE_2__ rrw_node_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rrw_tsd_key ; 
 TYPE_2__* tsd_get (int /*<<< orphan*/ ) ; 
 scalar_t__ tsd_set (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
rrn_find_and_remove(rrwlock_t *rrl, void *tag)
{
	rrw_node_t *rn;
	rrw_node_t *prev = NULL;

	if (zfs_refcount_count(&rrl->rr_linked_rcount) == 0)
		return (B_FALSE);

	for (rn = tsd_get(rrw_tsd_key); rn != NULL; rn = rn->rn_next) {
		if (rn->rn_rrl == rrl && rn->rn_tag == tag) {
			if (prev)
				prev->rn_next = rn->rn_next;
			else
				VERIFY(tsd_set(rrw_tsd_key, rn->rn_next) == 0);
			kmem_free(rn, sizeof (*rn));
			return (B_TRUE);
		}
		prev = rn;
	}
	return (B_FALSE);
}