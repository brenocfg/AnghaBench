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
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_invalidate_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_catalog_insert(Relation rel, HeapTuple tuple)
{
	CatalogTupleInsert(rel, tuple);
	ts_catalog_invalidate_cache(RelationGetRelid(rel), CMD_INSERT);
	/* Make changes visible */
	CommandCounterIncrement();
}