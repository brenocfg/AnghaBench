#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  relid; TYPE_1__* reltarget; } ;
struct TYPE_4__ {int /*<<< orphan*/  exprs; } ;
typedef  TYPE_2__ RelOptInfo ;

/* Variables and functions */
 int /*<<< orphan*/  get_atttype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compressed_reltarget_add_whole_row_var(RelOptInfo *compressed_rel)
{
	compressed_rel->reltarget->exprs =
		lappend(compressed_rel->reltarget->exprs,
				makeVar(compressed_rel->relid, 0, get_atttype(compressed_rel->relid, 0), -1, 0, 0));
}