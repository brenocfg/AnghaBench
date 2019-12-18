#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ms_allocator; int /*<<< orphan*/  ms_start; int /*<<< orphan*/  ms_weight; scalar_t__ ms_primary; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMPLY (int,int) ; 
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
metaslab_compare(const void *x1, const void *x2)
{
	const metaslab_t *m1 = (const metaslab_t *)x1;
	const metaslab_t *m2 = (const metaslab_t *)x2;

	int sort1 = 0;
	int sort2 = 0;
	if (m1->ms_allocator != -1 && m1->ms_primary)
		sort1 = 1;
	else if (m1->ms_allocator != -1 && !m1->ms_primary)
		sort1 = 2;
	if (m2->ms_allocator != -1 && m2->ms_primary)
		sort2 = 1;
	else if (m2->ms_allocator != -1 && !m2->ms_primary)
		sort2 = 2;

	/*
	 * Sort inactive metaslabs first, then primaries, then secondaries. When
	 * selecting a metaslab to allocate from, an allocator first tries its
	 * primary, then secondary active metaslab. If it doesn't have active
	 * metaslabs, or can't allocate from them, it searches for an inactive
	 * metaslab to activate. If it can't find a suitable one, it will steal
	 * a primary or secondary metaslab from another allocator.
	 */
	if (sort1 < sort2)
		return (-1);
	if (sort1 > sort2)
		return (1);

	int cmp = TREE_CMP(m2->ms_weight, m1->ms_weight);
	if (likely(cmp))
		return (cmp);

	IMPLY(TREE_CMP(m1->ms_start, m2->ms_start) == 0, m1 == m2);

	return (TREE_CMP(m1->ms_start, m2->ms_start));
}