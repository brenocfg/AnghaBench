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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (char const*,int) ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_namespace_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
hypertable_check_associated_schema_permissions(const char *schema_name, Oid user_oid)
{
	Oid schema_oid;

	/*
	 * If the schema name is NULL, it implies the internal catalog schema and
	 * anyone should be able to create chunks there.
	 */
	if (NULL == schema_name)
		return InvalidOid;

	schema_oid = get_namespace_oid(schema_name, true);

	/* Anyone can create chunks in the internal schema */
	if (strncmp(schema_name, INTERNAL_SCHEMA_NAME, NAMEDATALEN) == 0)
	{
		Assert(OidIsValid(schema_oid));
		return schema_oid;
	}

	if (!OidIsValid(schema_oid))
	{
		/*
		 * Schema does not exist, so we must check that the user has
		 * privileges to create the schema in the current database
		 */
		if (pg_database_aclcheck(MyDatabaseId, user_oid, ACL_CREATE) != ACLCHECK_OK)
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permissions denied: cannot create schema \"%s\" in database \"%s\"",
							schema_name,
							get_database_name(MyDatabaseId))));
	}
	else if (pg_namespace_aclcheck(schema_oid, user_oid, ACL_CREATE) != ACLCHECK_OK)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permissions denied: cannot create chunks in schema \"%s\"", schema_name)));

	return schema_oid;
}