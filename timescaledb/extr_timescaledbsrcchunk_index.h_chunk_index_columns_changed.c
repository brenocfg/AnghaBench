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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_3__ {int natts; int tdhasoid; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
chunk_index_columns_changed(int hypertable_natts, bool hypertable_has_oid, TupleDesc chunkdesc)
{
	/*
	 * We should be able to safely assume that the only reason the number of
	 * attributes differ is because we have removed columns in the base table,
	 * leaving junk attributes that aren't inherited by the chunk.
	 */
	return !(hypertable_natts == chunkdesc->natts && hypertable_has_oid == chunkdesc->tdhasoid);
}