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
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  space; } ;
typedef  TYPE_1__ ChunkScanCtx ;
typedef  int /*<<< orphan*/  ChunkResult ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_DONE ; 
 int /*<<< orphan*/  CHUNK_IGNORED ; 
 int /*<<< orphan*/  CHUNK_PROCESSED ; 
 scalar_t__ chunk_is_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChunkResult
set_complete_chunk(ChunkScanCtx *scanctx, Chunk *chunk)
{
	if (chunk_is_complete(chunk, scanctx->space))
	{
		scanctx->data = chunk;
#ifdef USE_ASSERT_CHECKING
		return CHUNK_PROCESSED;
#else
		return CHUNK_DONE;
#endif
	}
	return CHUNK_IGNORED;
}