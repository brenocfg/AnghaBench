#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * Name ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Cache ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERRCODE_TS_TABLESPACE_ALREADY_ATTACHED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  GetUserNameFromId (scalar_t__,int) ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_rel_name (scalar_t__) ; 
 scalar_t__ get_tablespace_oid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pg_tablespace_aclcheck (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tablespace_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 TYPE_2__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 scalar_t__ ts_hypertable_has_tablespace (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ts_hypertable_permissions_check (scalar_t__,int /*<<< orphan*/ ) ; 

void
ts_tablespace_attach_internal(Name tspcname, Oid hypertable_oid, bool if_not_attached)
{
	Cache *hcache;
	Hypertable *ht;
	Oid tspc_oid;
	Oid ownerid;
	AclResult aclresult;
	CatalogSecurityContext sec_ctx;

	if (NULL == tspcname)
		elog(ERROR, "invalid tablespace name");

	if (!OidIsValid(hypertable_oid))
		elog(ERROR, "invalid hypertable");

	tspc_oid = get_tablespace_oid(NameStr(*tspcname), true);

	if (!OidIsValid(tspc_oid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("tablespace \"%s\" does not exist", NameStr(*tspcname)),
				 errhint("The tablespace needs to be created"
						 " before attaching it to a hypertable.")));

	ownerid = ts_hypertable_permissions_check(hypertable_oid, GetUserId());

	/*
	 * Only check permissions on tablespace if it is not the database default.
	 * In usual case users can create tables in their database which will use
	 * the default tablespace of the database. This condition makes sure they
	 * can also always move a table from another tablespace to the default of
	 * their own database. Related to this issue in postgres core:
	 * https://www.postgresql.org/message-id/52DC8AEA.7090507%402ndquadrant.com
	 * Which was handled in a similar way. (See
	 * tablecmds.c::ATPrepSetTableSpace)
	 */
	if (tspc_oid != MyDatabaseTableSpace)
	{
		/*
		 * Note that we check against the table owner rather than the current
		 * user here, since we're not actually creating a table using this
		 * tablespace at this point
		 */
		aclresult = pg_tablespace_aclcheck(tspc_oid, ownerid, ACL_CREATE);

		if (aclresult != ACLCHECK_OK)
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied for tablespace \"%s\" by table owner \"%s\"",
							NameStr(*tspcname),
							GetUserNameFromId(ownerid, true))));
	}
	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, hypertable_oid);

	if (NULL == ht)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("table \"%s\" is not a hypertable", get_rel_name(hypertable_oid))));

	if (ts_hypertable_has_tablespace(ht, tspc_oid))
	{
		if (if_not_attached)
			ereport(NOTICE,
					(errcode(ERRCODE_TS_TABLESPACE_ALREADY_ATTACHED),
					 errmsg("tablespace \"%s\" is already attached to hypertable \"%s\", skipping",
							NameStr(*tspcname),
							get_rel_name(hypertable_oid))));
		else
			ereport(ERROR,
					(errcode(ERRCODE_TS_TABLESPACE_ALREADY_ATTACHED),
					 errmsg("tablespace \"%s\" is already attached to hypertable \"%s\"",
							NameStr(*tspcname),
							get_rel_name(hypertable_oid))));
	}
	else
	{
		ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
		tablespace_insert(ht->fd.id, NameStr(*tspcname));
		ts_catalog_restore_user(&sec_ctx);
	}

	ts_cache_release(hcache);
}