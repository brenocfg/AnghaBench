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
typedef  int /*<<< orphan*/  zpool_list_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  get_stat_flags_cb ; 
 int /*<<< orphan*/  pool_list_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint64_t
get_stat_flags(zpool_list_t *list)
{
	uint64_t mask = -1;

	/*
	 * get_stat_flags_cb() will lop off bits from "mask" until only the
	 * flags that are supported on all pools remain.
	 */
	pool_list_iter(list, B_FALSE, get_stat_flags_cb, &mask);
	return (mask);
}