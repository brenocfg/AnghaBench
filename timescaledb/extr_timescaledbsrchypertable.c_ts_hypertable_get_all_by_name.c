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
struct TYPE_3__ {int /*<<< orphan*/ * ht_oids; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
typedef  int /*<<< orphan*/  Name ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Catalog ;
typedef  TYPE_1__ AccumHypertable ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  HYPERTABLE ; 
 int /*<<< orphan*/  INVALID_INDEXID ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_scan_limit_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_tuple_match_name ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

List *
ts_hypertable_get_all_by_name(Name schema_name, Name table_name, MemoryContext mctx)
{
	Catalog *catalog = ts_catalog_get();
	AccumHypertable data = {
		.ht_oids = NIL,
		.schema_name = schema_name,
		.table_name = table_name,
	};

	hypertable_scan_limit_internal(NULL,
								   0,
								   catalog_get_index(catalog, HYPERTABLE, INVALID_INDEXID),
								   hypertable_tuple_match_name,
								   &data,
								   -1,
								   AccessShareLock,
								   false,
								   mctx);

	return data.ht_oids;
}