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
struct TYPE_2__ {int /*<<< orphan*/  dle_mintxg; } ;
typedef  TYPE_1__ dsl_deadlist_entry_t ;

/* Variables and functions */
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_deadlist_compare(const void *arg1, const void *arg2)
{
	const dsl_deadlist_entry_t *dle1 = arg1;
	const dsl_deadlist_entry_t *dle2 = arg2;

	return (TREE_CMP(dle1->dle_mintxg, dle2->dle_mintxg));
}