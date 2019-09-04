#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parsetree; } ;
typedef  TYPE_1__ CollectedCommand ;

/* Variables and functions */
#define  T_AlterTableStmt 129 
#define  T_CreateStmt 128 
 int nodeTag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_altertable_end (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_create_table_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_ddl_command_end(CollectedCommand *cmd)
{
	switch (nodeTag(cmd->parsetree))
	{
		case T_CreateStmt:
			process_create_table_end(cmd->parsetree);
			break;
		case T_AlterTableStmt:
			process_altertable_end(cmd->parsetree, cmd);
			break;
		default:
			break;
	}
}