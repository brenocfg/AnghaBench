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
typedef  int /*<<< orphan*/  dsl_deadlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_deadlist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  livelist_entry_count_blocks_cb ; 

__attribute__((used)) static void
livelist_count_blocks(dsl_deadlist_t *ll, void *arg)
{
	dsl_deadlist_iterate(ll, livelist_entry_count_blocks_cb, arg);
}