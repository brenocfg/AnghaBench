#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  tdhasoid; int /*<<< orphan*/  natts; } ;

/* Variables and functions */
 int chunk_index_columns_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline bool
chunk_index_need_attnos_adjustment(TupleDesc htdesc, TupleDesc chunkdesc)
{
	return chunk_index_columns_changed(htdesc->natts, htdesc->tdhasoid, chunkdesc);
}