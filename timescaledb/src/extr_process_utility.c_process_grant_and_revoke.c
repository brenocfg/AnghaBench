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
struct TYPE_7__ {scalar_t__ targtype; int objtype; scalar_t__ is_grant; } ;
struct TYPE_6__ {scalar_t__ parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;
typedef  TYPE_2__ GrantStmt ;

/* Variables and functions */
#define  ACL_OBJECT_TABLESPACE 129 
 scalar_t__ ACL_TARGET_OBJECT ; 
#define  OBJECT_TABLESPACE 128 
 int /*<<< orphan*/  prev_ProcessUtility (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_tablespace_validate_revoke (TYPE_2__*) ; 

__attribute__((used)) static bool
process_grant_and_revoke(ProcessUtilityArgs *args)
{
	GrantStmt *stmt = (GrantStmt *) args->parsetree;

	/*
	 * Need to apply the REVOKE first to be able to check remaining
	 * permissions
	 */
	prev_ProcessUtility(args);

	/* We only care about revokes and setting privileges on a specific object */
	if (stmt->is_grant || stmt->targtype != ACL_TARGET_OBJECT)
		return true;

	switch (stmt->objtype)
	{
/*
 * PG11 consolidated several ACL_OBJECT_FOO or similar to the already extant
 * OBJECT_FOO see:
 * https://github.com/postgres/postgres/commit/2c6f37ed62114bd5a092c20fe721bd11b3bcb91e
 * so we can't simply #define OBJECT_TABLESPACE ACL_OBJECT_TABLESPACE and have
 * things work correctly for previous versions.
 */
#if PG11_LT
		case ACL_OBJECT_TABLESPACE:
#else
		case OBJECT_TABLESPACE:
#endif
			ts_tablespace_validate_revoke(stmt);
			break;
		default:
			break;
	}

	return true;
}