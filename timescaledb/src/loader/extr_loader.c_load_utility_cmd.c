#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
#define  T_AlterExtensionStmt 131 
#define  T_CreateExtensionStmt 130 
#define  T_DropStmt 129 
#define  T_VariableSetStmt 128 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int should_load_on_alter_extension (int /*<<< orphan*/ *) ; 
 int should_load_on_create_extension (int /*<<< orphan*/ *) ; 
 int should_load_on_drop_extension (int /*<<< orphan*/ *) ; 
 int should_load_on_variable_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
load_utility_cmd(Node *utility_stmt)
{
	switch (nodeTag(utility_stmt))
	{
		case T_VariableSetStmt:
			return should_load_on_variable_set(utility_stmt);
		case T_AlterExtensionStmt:
			return should_load_on_alter_extension(utility_stmt);
		case T_CreateExtensionStmt:
			return should_load_on_create_extension(utility_stmt);
		case T_DropStmt:
			return should_load_on_drop_extension(utility_stmt);
		default:
			return true;
	}
}