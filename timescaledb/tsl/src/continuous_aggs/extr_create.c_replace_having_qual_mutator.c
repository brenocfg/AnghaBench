#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int found; TYPE_2__* new; TYPE_1__* old; } ;
typedef  TYPE_3__ cagg_havingcxt ;
struct TYPE_8__ {scalar_t__ expr; } ;
struct TYPE_7__ {int /*<<< orphan*/  expr; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * expression_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,TYPE_3__*),TYPE_3__*) ; 

__attribute__((used)) static Node *
replace_having_qual_mutator(Node *node, cagg_havingcxt *cxt)
{
	if (node == NULL)
		return NULL;
	if (equal(node, cxt->old->expr))
	{
		cxt->found = true;
		return (Node *) cxt->new->expr;
	}
	return expression_tree_mutator(node, replace_having_qual_mutator, cxt);
}