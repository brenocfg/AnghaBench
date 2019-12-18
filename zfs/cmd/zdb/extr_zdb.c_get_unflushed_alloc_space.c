#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  count_unflushed_space_cb ; 
 scalar_t__* dump_opt ; 
 int /*<<< orphan*/  iterate_through_spacemap_logs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
get_unflushed_alloc_space(spa_t *spa)
{
	if (dump_opt['L'])
		return (0);

	int64_t ualloc_space = 0;
	iterate_through_spacemap_logs(spa, count_unflushed_space_cb,
	    &ualloc_space);
	return (ualloc_space);
}