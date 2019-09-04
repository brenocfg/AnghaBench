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
typedef  int /*<<< orphan*/  tuple_found_func ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ForwardScanDirection ; 
 int dimension_slice_scan_limit_direction_internal (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dimension_slice_scan_limit_internal(int indexid, ScanKeyData *scankey, int nkeys,
									tuple_found_func on_tuple_found, void *scandata, int limit,
									LOCKMODE lockmode, MemoryContext mctx)
{
	return dimension_slice_scan_limit_direction_internal(indexid,
														 scankey,
														 nkeys,
														 on_tuple_found,
														 scandata,
														 limit,
														 ForwardScanDirection,
														 lockmode,
														 mctx);
}