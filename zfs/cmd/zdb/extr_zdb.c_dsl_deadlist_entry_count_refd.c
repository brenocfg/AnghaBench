#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {TYPE_1__* spa_dsl_pool; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_9__ {scalar_t__ bpo_object; } ;
struct TYPE_8__ {TYPE_5__ dle_bpobj; } ;
typedef  TYPE_3__ dsl_deadlist_entry_t ;
struct TYPE_6__ {scalar_t__ dp_empty_bpobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpobj_count_refd (TYPE_5__*) ; 

__attribute__((used)) static int
dsl_deadlist_entry_count_refd(void *arg, dsl_deadlist_entry_t *dle)
{
	spa_t *spa = arg;
	uint64_t empty_bpobj = spa->spa_dsl_pool->dp_empty_bpobj;
	if (dle->dle_bpobj.bpo_object != empty_bpobj)
		bpobj_count_refd(&dle->dle_bpobj);
	return (0);
}