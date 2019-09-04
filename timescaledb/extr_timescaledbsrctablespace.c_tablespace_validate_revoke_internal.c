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
typedef  int /*<<< orphan*/  tuple_found_func ;
struct TYPE_3__ {void* data; int /*<<< orphan*/  hcache; int /*<<< orphan*/  database_info; } ;
typedef  TYPE_1__ TablespaceScanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  tablespace_scan_by_name (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_hypertable_cache_pin () ; 

__attribute__((used)) static void
tablespace_validate_revoke_internal(const char *tspcname, tuple_found_func tuple_found, void *stmt)
{
	TablespaceScanInfo info = {
		.database_info = ts_catalog_database_info_get(),
		.hcache = ts_hypertable_cache_pin(),
		.data = stmt,
	};

	tablespace_scan_by_name(tspcname, tuple_found, &info);

	ts_cache_release(info.hcache);
}