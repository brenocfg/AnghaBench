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
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERRCODE_TS_TABLESPACE_NOT_ATTACHED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_2__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 scalar_t__ ts_hypertable_has_tablespace (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_tablespace_delete (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
tablespace_detach_one(Oid hypertable_oid, const char *tspcname, Oid tspcoid, bool if_attached)
{
	Cache *hcache;
	Hypertable *ht;
	int ret = 0;

	ts_hypertable_permissions_check(hypertable_oid, GetUserId());

	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, hypertable_oid);

	if (NULL == ht)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("table \"%s\" is not a hypertable", get_rel_name(hypertable_oid))));

	if (ts_hypertable_has_tablespace(ht, tspcoid))
		ret = ts_tablespace_delete(ht->fd.id, tspcname);
	else if (if_attached)
		ereport(NOTICE,
				(errcode(ERRCODE_TS_TABLESPACE_NOT_ATTACHED),
				 errmsg("tablespace \"%s\" is not attached to hypertable \"%s\", skipping",
						tspcname,
						get_rel_name(hypertable_oid))));
	else
		ereport(ERROR,
				(errcode(ERRCODE_TS_TABLESPACE_NOT_ATTACHED),
				 errmsg("tablespace \"%s\" is not attached to hypertable \"%s\"",
						tspcname,
						get_rel_name(hypertable_oid))));

	ts_cache_release(hcache);

	return ret;
}