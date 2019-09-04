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
struct TYPE_2__ {int kind; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ VariableSetStmt ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_DISABLE_LOAD_NAME ; 
#define  VAR_RESET 130 
#define  VAR_SET_DEFAULT 129 
#define  VAR_SET_VALUE 128 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
should_load_on_variable_set(Node *utility_stmt)
{
	VariableSetStmt *stmt = (VariableSetStmt *) utility_stmt;

	switch (stmt->kind)
	{
		case VAR_SET_VALUE:
		case VAR_SET_DEFAULT:
		case VAR_RESET:
			/* Do not load when setting the guc to disable load */
			return stmt->name == NULL || strcmp(stmt->name, GUC_DISABLE_LOAD_NAME) != 0;
		default:
			return true;
	}
}