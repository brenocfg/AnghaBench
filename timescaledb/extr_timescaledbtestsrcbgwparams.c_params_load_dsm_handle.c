#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_handle ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  TYPE_1__ FormData_bgw_dsm_handle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  get_dsm_handle_table_oid () ; 
 int /*<<< orphan*/  heap_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dsm_handle
params_load_dsm_handle()
{
	Relation rel;
	HeapScanDesc scan;
	HeapTuple tuple;
	FormData_bgw_dsm_handle *fd;
	dsm_handle handle;

	rel = heap_open(get_dsm_handle_table_oid(), RowExclusiveLock);
	scan = heap_beginscan(rel, SnapshotSelf, 0, NULL);
	tuple = heap_getnext(scan, ForwardScanDirection);
	Assert(tuple != NULL);
	tuple = heap_copytuple(tuple);
	fd = (FormData_bgw_dsm_handle *) GETSTRUCT(tuple);
	handle = fd->handle;
	heap_freetuple(tuple);
	heap_endscan(scan);
	heap_close(rel, RowExclusiveLock);

	return handle;
}