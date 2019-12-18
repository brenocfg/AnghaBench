#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * mm_path; } ;
struct TYPE_5__ {TYPE_1__* pathtarget; } ;
struct TYPE_4__ {int /*<<< orphan*/ * exprs; } ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ MutatorContext ;
typedef  int /*<<< orphan*/  MinMaxAggPath ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ mutate_aggref_node (int /*<<< orphan*/ *,void*) ; 

void
replace_aggref_in_tlist(MinMaxAggPath *minmaxagg_path)
{
	MutatorContext context;

	context.mm_path = minmaxagg_path;

	((Path *) minmaxagg_path)->pathtarget->exprs =
		(List *) mutate_aggref_node((Node *) ((Path *) minmaxagg_path)->pathtarget->exprs,
									(void *) &context);
}