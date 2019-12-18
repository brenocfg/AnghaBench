#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  multilist_t ;
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_4__ {int /*<<< orphan*/ ** arcs_list; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** arcs_list; } ;

/* Variables and functions */
 size_t ARC_BUFC_DATA ; 
 size_t ARC_BUFC_METADATA ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int L2ARC_FEED_TYPES ; 
 TYPE_2__* arc_mfu ; 
 TYPE_1__* arc_mru ; 
 unsigned int multilist_get_random_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * multilist_sublist_lock (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static multilist_sublist_t *
l2arc_sublist_lock(int list_num)
{
	multilist_t *ml = NULL;
	unsigned int idx;

	ASSERT(list_num >= 0 && list_num < L2ARC_FEED_TYPES);

	switch (list_num) {
	case 0:
		ml = arc_mfu->arcs_list[ARC_BUFC_METADATA];
		break;
	case 1:
		ml = arc_mru->arcs_list[ARC_BUFC_METADATA];
		break;
	case 2:
		ml = arc_mfu->arcs_list[ARC_BUFC_DATA];
		break;
	case 3:
		ml = arc_mru->arcs_list[ARC_BUFC_DATA];
		break;
	default:
		return (NULL);
	}

	/*
	 * Return a randomly-selected sublist. This is acceptable
	 * because the caller feeds only a little bit of data for each
	 * call (8MB). Subsequent calls will result in different
	 * sublists being selected.
	 */
	idx = multilist_get_random_index(ml);
	return (multilist_sublist_lock(ml, idx));
}