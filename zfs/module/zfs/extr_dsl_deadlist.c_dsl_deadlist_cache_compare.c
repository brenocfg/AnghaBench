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
struct TYPE_2__ {int /*<<< orphan*/  dlce_mintxg; } ;
typedef  TYPE_1__ dsl_deadlist_cache_entry_t ;

/* Variables and functions */
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_deadlist_cache_compare(const void *arg1, const void *arg2)
{
	const dsl_deadlist_cache_entry_t *dlce1 = arg1;
	const dsl_deadlist_cache_entry_t *dlce2 = arg2;

	return (TREE_CMP(dlce1->dlce_mintxg, dlce2->dlce_mintxg));
}