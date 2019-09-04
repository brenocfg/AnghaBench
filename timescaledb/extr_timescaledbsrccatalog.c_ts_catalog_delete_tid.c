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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_invalidate_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_catalog_delete_tid(Relation rel, ItemPointer tid)
{
	CatalogTupleDelete(rel, tid);
	ts_catalog_invalidate_cache(RelationGetRelid(rel), CMD_DELETE);
	CommandCounterIncrement();
}