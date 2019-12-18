#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ distinctClause; scalar_t__ targetList; scalar_t__ windowClause; scalar_t__ lockingClause; scalar_t__ op; int all; int /*<<< orphan*/ * rarg; int /*<<< orphan*/ * larg; int /*<<< orphan*/ * withClause; int /*<<< orphan*/ * limitCount; int /*<<< orphan*/ * limitOffset; int /*<<< orphan*/ * valuesLists; int /*<<< orphan*/ * havingClause; int /*<<< orphan*/ * whereClause; int /*<<< orphan*/ * intoClause; } ;
typedef  TYPE_1__ SelectStmt ;

/* Variables and functions */
 scalar_t__ NIL ; 

__attribute__((used)) static bool
select_stmt_as_expected(SelectStmt *stmt)
{
	/* The only parts of the select stmt that are allowed to be set are the order by or group by.
	 * Check that no other fields are set */
	if (stmt->distinctClause != NIL || stmt->intoClause != NULL || stmt->targetList != NIL ||
		stmt->whereClause != NULL || stmt->havingClause != NULL || stmt->windowClause != NIL ||
		stmt->valuesLists != NULL || stmt->limitOffset != NULL || stmt->limitCount != NULL ||
		stmt->lockingClause != NIL || stmt->withClause != NULL || stmt->op != 0 ||
		stmt->all != false || stmt->larg != NULL || stmt->rarg != NULL)
		return false;
	return true;
}