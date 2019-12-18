#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {scalar_t__ sr_refcnt; unsigned long long sr_offset; } ;
typedef  TYPE_1__ space_ref_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ *,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
space_reftree_generate_map(avl_tree_t *t, range_tree_t *rt, int64_t minref)
{
	uint64_t start = -1ULL;
	int64_t refcnt = 0;
	space_ref_t *sr;

	range_tree_vacate(rt, NULL, NULL);

	for (sr = avl_first(t); sr != NULL; sr = AVL_NEXT(t, sr)) {
		refcnt += sr->sr_refcnt;
		if (refcnt >= minref) {
			if (start == -1ULL) {
				start = sr->sr_offset;
			}
		} else {
			if (start != -1ULL) {
				uint64_t end = sr->sr_offset;
				ASSERT(start <= end);
				if (end > start)
					range_tree_add(rt, start, end - start);
				start = -1ULL;
			}
		}
	}
	ASSERT(refcnt == 0);
	ASSERT(start == -1ULL);
}