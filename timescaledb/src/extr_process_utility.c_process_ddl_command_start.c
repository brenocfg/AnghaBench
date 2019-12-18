#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;

/* Variables and functions */
#define  T_AlterObjectSchemaStmt 144 
#define  T_AlterTableStmt 143 
#define  T_ClusterStmt 142 
#define  T_CopyStmt 141 
#define  T_CreateTrigStmt 140 
#define  T_DropStmt 139 
#define  T_DropTableSpaceStmt 138 
#define  T_GrantRoleStmt 137 
#define  T_GrantStmt 136 
#define  T_IndexStmt 135 
#define  T_RefreshMatViewStmt 134 
#define  T_ReindexStmt 133 
#define  T_RenameStmt 132 
#define  T_RuleStmt 131 
#define  T_TruncateStmt 130 
#define  T_VacuumStmt 129 
#define  T_ViewStmt 128 
 int nodeTag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_alterobjectschema (TYPE_1__*) ; 
 int process_altertable_start (TYPE_1__*) ; 
 int process_cluster_start (TYPE_1__*) ; 
 int process_copy (TYPE_1__*) ; 
 int /*<<< orphan*/  process_create_rule_start (TYPE_1__*) ; 
 int process_create_trigger_start (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_tablespace (TYPE_1__*) ; 
 int process_grant_and_revoke (TYPE_1__*) ; 
 int process_grant_and_revoke_role (TYPE_1__*) ; 
 int process_index_start (TYPE_1__*) ; 
 int process_refresh_mat_view_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int process_reindex (TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename (TYPE_1__*) ; 
 int process_truncate (TYPE_1__*) ; 
 int process_vacuum (TYPE_1__*) ; 
 int process_viewstmt (TYPE_1__*) ; 

__attribute__((used)) static bool
process_ddl_command_start(ProcessUtilityArgs *args)
{
	bool handled = false;

	switch (nodeTag(args->parsetree))
	{
		case T_AlterObjectSchemaStmt:
			process_alterobjectschema(args);
			break;
		case T_TruncateStmt:
			handled = process_truncate(args);
			break;
		case T_AlterTableStmt:
			handled = process_altertable_start(args);
			break;
		case T_RenameStmt:
			process_rename(args);
			break;
		case T_IndexStmt:
			handled = process_index_start(args);
			break;
		case T_CreateTrigStmt:
			handled = process_create_trigger_start(args);
			break;
		case T_RuleStmt:
			process_create_rule_start(args);
			break;
		case T_DropStmt:

			/*
			 * Drop associated metadata/chunks but also continue on to drop
			 * the main table. Because chunks are deleted before the main
			 * table is dropped, the drop respects CASCADE in the expected
			 * way.
			 */
			process_drop(args);
			break;
		case T_DropTableSpaceStmt:
			process_drop_tablespace(args);
			break;
		case T_GrantStmt:
			handled = process_grant_and_revoke(args);
			break;
		case T_GrantRoleStmt:
			handled = process_grant_and_revoke_role(args);
			break;
		case T_CopyStmt:
			handled = process_copy(args);
			break;
		case T_VacuumStmt:
			handled = process_vacuum(args);
			break;
		case T_ReindexStmt:
			handled = process_reindex(args);
			break;
		case T_ClusterStmt:
			handled = process_cluster_start(args);
			break;
		case T_ViewStmt:
			handled = process_viewstmt(args);
			break;
		case T_RefreshMatViewStmt:
			handled = process_refresh_mat_view_start(args, args->parsetree);
			break;
		default:
			break;
	}

	return handled;
}