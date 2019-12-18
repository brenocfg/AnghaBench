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
typedef  int /*<<< orphan*/  TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  ChunkIndexMapping ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  chunk_index_mapping_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static ScanTupleResult
chunk_index_tuple_found(TupleInfo *ti, void *const data)
{
	ChunkIndexMapping *const cim = data;

	chunk_index_mapping_from_tuple(ti, cim);
	return SCAN_DONE;
}