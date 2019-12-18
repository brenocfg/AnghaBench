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
struct TYPE_3__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ ChunkDispatch ;

/* Variables and functions */
 int /*<<< orphan*/  ts_subspace_store_free (int /*<<< orphan*/ ) ; 

void
ts_chunk_dispatch_destroy(ChunkDispatch *cd)
{
	ts_subspace_store_free(cd->cache);
}