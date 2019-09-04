#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  args; } ;
struct TYPE_8__ {int isnull; } ;
struct TYPE_7__ {int isnull; } ;
struct TYPE_9__ {void* lookup_after; void* lookup_before; TYPE_2__ next; TYPE_1__ prev; } ;
typedef  int /*<<< orphan*/  GapFillState ;
typedef  TYPE_3__ GapFillInterpolateColumnState ;
typedef  TYPE_4__ FuncExpr ;

/* Variables and functions */
 void* gapfill_adjust_varnos (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lthird (int /*<<< orphan*/ ) ; 

void
gapfill_interpolate_initialize(GapFillInterpolateColumnState *interpolate, GapFillState *state,
							   FuncExpr *function)
{
	interpolate->prev.isnull = true;
	interpolate->next.isnull = true;
	if (list_length(((FuncExpr *) function)->args) > 1)
		interpolate->lookup_before =
			gapfill_adjust_varnos(state, lsecond(((FuncExpr *) function)->args));
	if (list_length(((FuncExpr *) function)->args) > 2)
		interpolate->lookup_after =
			gapfill_adjust_varnos(state, lthird(((FuncExpr *) function)->args));
}