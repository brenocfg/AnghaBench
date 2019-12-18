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
struct TYPE_3__ {scalar_t__ num_filtered; int /*<<< orphan*/  hcache; int /*<<< orphan*/  userid; int /*<<< orphan*/  database_info; } ;
typedef  TYPE_1__ TablespaceScanInfo ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_tablespace_tablespace_name ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  INVALID_INDEXID ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  namein ; 
 int tablespace_scan_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tablespace_tuple_delete ; 
 int /*<<< orphan*/  tablespace_tuple_owner_filter ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_hypertable_cache_pin () ; 

__attribute__((used)) static int
tablespace_delete_from_all(const char *tspcname, Oid userid)
{
	ScanKeyData scankey[1];
	TablespaceScanInfo info = {
		.database_info = ts_catalog_database_info_get(),
		.hcache = ts_hypertable_cache_pin(),
		.userid = userid,
	};
	int num_deleted;

	ScanKeyInit(&scankey[0],
				Anum_tablespace_tablespace_name,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				DirectFunctionCall1(namein, CStringGetDatum(tspcname)));

	num_deleted = tablespace_scan_internal(INVALID_INDEXID,
										   scankey,
										   1,
										   tablespace_tuple_delete,
										   tablespace_tuple_owner_filter,
										   &info,
										   0,
										   RowExclusiveLock);
	ts_cache_release(info.hcache);

	if (num_deleted > 0)
		CommandCounterIncrement();

	if (info.num_filtered > 0)
		ereport(NOTICE,
				(errmsg("tablespace \"%s\" remains attached to %d hypertable(s) due to lack of "
						"permissions",
						tspcname,
						info.num_filtered)));

	return num_deleted;
}