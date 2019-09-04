#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_8__ {int /*<<< orphan*/  num_filtered; int /*<<< orphan*/  userid; int /*<<< orphan*/  hcache; } ;
typedef  TYPE_2__ TablespaceScanInfo ;
struct TYPE_10__ {int /*<<< orphan*/  hypertable_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  main_table_relid; } ;
typedef  int /*<<< orphan*/  ScanFilterResult ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ FormData_tablespace ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_EXCLUDE ; 
 int /*<<< orphan*/  SCAN_INCLUDE ; 
 TYPE_3__* ts_hypertable_cache_get_entry_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_hypertable_has_privs_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanFilterResult
tablespace_tuple_owner_filter(TupleInfo *ti, void *data)
{
	TablespaceScanInfo *info = data;
	FormData_tablespace *form = (FormData_tablespace *) GETSTRUCT(ti->tuple);
	Hypertable *ht;

	ht = ts_hypertable_cache_get_entry_by_id(info->hcache, form->hypertable_id);

	Assert(NULL != ht);

	if (ts_hypertable_has_privs_of(ht->main_table_relid, info->userid))
		return SCAN_INCLUDE;

	info->num_filtered++;

	return SCAN_EXCLUDE;
}