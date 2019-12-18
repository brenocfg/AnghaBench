#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ChunkScanCtx ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int chunk_scan_ctx_foreach_chunk (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_complete_chunk ; 

__attribute__((used)) static Chunk *
chunk_scan_ctx_get_chunk(ChunkScanCtx *ctx)
{
	ctx->data = NULL;

#ifdef USE_ASSERT_CHECKING
	{
		int n = chunk_scan_ctx_foreach_chunk(ctx, set_complete_chunk, 0);

		Assert(n == 0 || n == 1);
	}
#else
	chunk_scan_ctx_foreach_chunk(ctx, set_complete_chunk, 1);
#endif

	return ctx->data;
}