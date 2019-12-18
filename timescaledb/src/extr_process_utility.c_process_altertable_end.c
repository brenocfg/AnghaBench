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
struct TYPE_2__ {int relkind; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  CollectedCommand ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
#define  OBJECT_INDEX 129 
#define  OBJECT_TABLE 128 
 int /*<<< orphan*/  process_altertable_end_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_altertable_end_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_altertable_end(Node *parsetree, CollectedCommand *cmd)
{
	AlterTableStmt *stmt = (AlterTableStmt *) parsetree;

	switch (stmt->relkind)
	{
		case OBJECT_TABLE:
			process_altertable_end_table(parsetree, cmd);
			break;
		case OBJECT_INDEX:
			process_altertable_end_index(parsetree, cmd);
			break;
		default:
			break;
	}
}