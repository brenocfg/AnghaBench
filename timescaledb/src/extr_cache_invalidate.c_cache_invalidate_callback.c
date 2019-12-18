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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_TYPE_BGW_JOB ; 
 int /*<<< orphan*/  CACHE_TYPE_HYPERTABLE ; 
 int /*<<< orphan*/  cache_invalidate_all () ; 
 int /*<<< orphan*/  ts_bgw_job_cache_invalidate_callback () ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 scalar_t__ ts_catalog_get_cache_proxy_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_extension_invalidate (scalar_t__) ; 
 int /*<<< orphan*/  ts_extension_is_loaded () ; 
 int /*<<< orphan*/  ts_hypertable_cache_invalidate_callback () ; 

__attribute__((used)) static void
cache_invalidate_callback(Datum arg, Oid relid)
{
	Catalog *catalog;

	if (ts_extension_invalidate(relid))
	{
		cache_invalidate_all();
		return;
	}

	if (!ts_extension_is_loaded())
		return;

	catalog = ts_catalog_get();

	if (relid == ts_catalog_get_cache_proxy_id(catalog, CACHE_TYPE_HYPERTABLE))
		ts_hypertable_cache_invalidate_callback();

	if (relid == ts_catalog_get_cache_proxy_id(catalog, CACHE_TYPE_BGW_JOB))
		ts_bgw_job_cache_invalidate_callback();
}