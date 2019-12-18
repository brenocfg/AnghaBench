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
struct TYPE_2__ {scalar_t__ aggsplit; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ AGGSPLIT_INITIAL_SERIAL ; 
 int /*<<< orphan*/  Aggref ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int expression_tree_walker (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 

__attribute__((used)) static bool
ensure_only_partials(Node *node, void *state)
{
	if (node == NULL)
		return false;

	if (IsA(node, Aggref) && castNode(Aggref, node)->aggsplit != AGGSPLIT_INITIAL_SERIAL)
		elog(ERROR, "Cannot mix partialized and non-partialized aggregates in the same statement");

	return expression_tree_walker((Node *) node, ensure_only_partials, state);
}