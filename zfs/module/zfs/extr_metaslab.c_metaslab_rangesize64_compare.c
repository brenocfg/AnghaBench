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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ rs_start; scalar_t__ rs_end; } ;
typedef  TYPE_1__ range_seg64_t ;

/* Variables and functions */
 int TREE_CMP (scalar_t__,scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
metaslab_rangesize64_compare(const void *x1, const void *x2)
{
	const range_seg64_t *r1 = x1;
	const range_seg64_t *r2 = x2;

	uint64_t rs_size1 = r1->rs_end - r1->rs_start;
	uint64_t rs_size2 = r2->rs_end - r2->rs_start;

	int cmp = TREE_CMP(rs_size1, rs_size2);
	if (likely(cmp))
		return (cmp);

	return (TREE_CMP(r1->rs_start, r2->rs_start));
}