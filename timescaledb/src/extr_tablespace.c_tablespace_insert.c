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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TABLESPACE ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tablespace_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

__attribute__((used)) static int32
tablespace_insert(int32 hypertable_id, const char *tspcname)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;
	int32 id;

	rel = heap_open(catalog_get_table_id(catalog, TABLESPACE), RowExclusiveLock);
	id = tablespace_insert_relation(rel, hypertable_id, tspcname);
	heap_close(rel, RowExclusiveLock);

	return id;
}