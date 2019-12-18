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
struct TYPE_3__ {int num_constraints; int /*<<< orphan*/ * constraints; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ChunkConstraints ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_CONSTRAINT ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_constraint_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
chunk_constraints_insert(ChunkConstraints *ccs)
{
	Catalog *catalog = ts_catalog_get();
	CatalogSecurityContext sec_ctx;
	Relation rel;
	int i;

	rel = heap_open(catalog_get_table_id(catalog, CHUNK_CONSTRAINT), RowExclusiveLock);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);

	for (i = 0; i < ccs->num_constraints; i++)
		chunk_constraint_insert_relation(rel, &ccs->constraints[i]);

	ts_catalog_restore_user(&sec_ctx);
	heap_close(rel, RowExclusiveLock);
}