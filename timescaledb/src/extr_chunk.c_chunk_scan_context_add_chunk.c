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
struct TYPE_3__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ ChunkScanCtx ;
typedef  int /*<<< orphan*/  ChunkResult ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_PROCESSED ; 
 int /*<<< orphan*/  chunk_fill_stub (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ChunkResult
chunk_scan_context_add_chunk(ChunkScanCtx *scanctx, Chunk *chunk)
{
	Chunk **chunks = (Chunk **) scanctx->data;

	chunk_fill_stub(chunk, false);
	*chunks = chunk;
	scanctx->data = chunks + 1;
	return CHUNK_PROCESSED;
}