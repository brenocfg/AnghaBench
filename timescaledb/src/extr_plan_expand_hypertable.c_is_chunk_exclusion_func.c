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
struct TYPE_2__ {scalar_t__ funcid; } ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  FuncExpr ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ chunk_exclusion_func ; 

__attribute__((used)) static bool
is_chunk_exclusion_func(Expr *node)
{
	if (IsA(node, FuncExpr) && castNode(FuncExpr, node)->funcid == chunk_exclusion_func)
		return true;

	return false;
}