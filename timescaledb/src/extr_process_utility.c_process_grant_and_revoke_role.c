#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ is_grant; } ;
struct TYPE_6__ {scalar_t__ parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;
typedef  TYPE_2__ GrantRoleStmt ;

/* Variables and functions */
 int /*<<< orphan*/  prev_ProcessUtility (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_tablespace_validate_revoke_role (TYPE_2__*) ; 

__attribute__((used)) static bool
process_grant_and_revoke_role(ProcessUtilityArgs *args)
{
	GrantRoleStmt *stmt = (GrantRoleStmt *) args->parsetree;

	/*
	 * Need to apply the REVOKE first to be able to check remaining
	 * permissions
	 */
	prev_ProcessUtility(args);

	/* We only care about revokes and setting privileges on a specific object */
	if (stmt->is_grant)
		return true;

	ts_tablespace_validate_revoke_role(stmt);

	return true;
}