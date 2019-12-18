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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ChunkIndexMapping ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/ * chunk_index_mapping_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
chunk_index_collect(TupleInfo *ti, void *data)
{
	List **mappings = data;
	ChunkIndexMapping *cim = chunk_index_mapping_from_tuple(ti, NULL);

	*mappings = lappend(*mappings, cim);

	return SCAN_CONTINUE;
}