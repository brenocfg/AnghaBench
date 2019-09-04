#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_5__ {int /*<<< orphan*/  associated_schema_name; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FormData_hypertable ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
reset_associated_tuple_found(TupleInfo *ti, void *data)
{
	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_hypertable *form = (FormData_hypertable *) GETSTRUCT(tuple);
	CatalogSecurityContext sec_ctx;

	namestrcpy(&form->associated_schema_name, INTERNAL_SCHEMA_NAME);
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_update(ti->scanrel, tuple);
	ts_catalog_restore_user(&sec_ctx);

	heap_freetuple(tuple);

	return SCAN_CONTINUE;
}