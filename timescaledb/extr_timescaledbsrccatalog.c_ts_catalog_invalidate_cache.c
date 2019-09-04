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
typedef  int /*<<< orphan*/  CmdType ;
typedef  int CatalogTable ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
#define  BGW_JOB 134 
 int /*<<< orphan*/  CACHE_TYPE_BGW_JOB ; 
 int /*<<< orphan*/  CACHE_TYPE_HYPERTABLE ; 
#define  CHUNK 133 
#define  CHUNK_CONSTRAINT 132 
#define  CHUNK_INDEX 131 
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CMD_UPDATE ; 
 int /*<<< orphan*/  CacheInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
#define  DIMENSION 130 
#define  DIMENSION_SLICE 129 
#define  HYPERTABLE 128 
 int catalog_get_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_get_cache_proxy_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ts_catalog_invalidate_cache(Oid catalog_relid, CmdType operation)
{
	Catalog *catalog = ts_catalog_get();
	CatalogTable table = catalog_get_table(catalog, catalog_relid);
	Oid relid;

	switch (table)
	{
		case CHUNK:
		case CHUNK_CONSTRAINT:
		case DIMENSION_SLICE:
			if (operation == CMD_UPDATE || operation == CMD_DELETE)
			{
				relid = ts_catalog_get_cache_proxy_id(catalog, CACHE_TYPE_HYPERTABLE);
				CacheInvalidateRelcacheByRelid(relid);
			}
			break;
		case HYPERTABLE:
		case DIMENSION:
			relid = ts_catalog_get_cache_proxy_id(catalog, CACHE_TYPE_HYPERTABLE);
			CacheInvalidateRelcacheByRelid(relid);
			break;
		case BGW_JOB:
			relid = ts_catalog_get_cache_proxy_id(catalog, CACHE_TYPE_BGW_JOB);
			CacheInvalidateRelcacheByRelid(relid);
			break;
		case CHUNK_INDEX:
		default:
			break;
	}
}