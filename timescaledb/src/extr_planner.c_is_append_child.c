#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int inh; scalar_t__ relkind; } ;
struct TYPE_5__ {scalar_t__ reloptkind; scalar_t__ rtekind; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;

/* Variables and functions */
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELOPT_OTHER_MEMBER_REL ; 
 scalar_t__ RTE_RELATION ; 

__attribute__((used)) static inline bool
is_append_child(RelOptInfo *rel, RangeTblEntry *rte)
{
	return rel->reloptkind == RELOPT_OTHER_MEMBER_REL && rte->inh == false &&
		   rel->rtekind == RTE_RELATION && rte->relkind == RELKIND_RELATION;
}