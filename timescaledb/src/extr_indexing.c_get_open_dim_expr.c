#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* partitioning; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fn_expr; } ;
struct TYPE_7__ {TYPE_1__ func_fmgr; } ;
struct TYPE_8__ {TYPE_2__ partfunc; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_4__ Dimension ;

/* Variables and functions */

__attribute__((used)) static Node *
get_open_dim_expr(Dimension *dim)
{
	if (dim == NULL || dim->partitioning == NULL)
		return NULL;

	return dim->partitioning->partfunc.func_fmgr.fn_expr;
}