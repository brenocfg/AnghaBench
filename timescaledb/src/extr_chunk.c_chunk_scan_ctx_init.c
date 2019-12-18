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
struct HASHCTL {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int early_abort; int /*<<< orphan*/  lockmode; scalar_t__ num_complete_chunks; int /*<<< orphan*/ * point; int /*<<< orphan*/ * space; int /*<<< orphan*/  htab; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  int /*<<< orphan*/  ChunkScanEntry ;
typedef  TYPE_1__ ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  hash_create (char*,int,struct HASHCTL*,int) ; 

__attribute__((used)) static void
chunk_scan_ctx_init(ChunkScanCtx *ctx, Hyperspace *hs, Point *p)
{
	struct HASHCTL hctl = {
		.keysize = sizeof(int32),
		.entrysize = sizeof(ChunkScanEntry),
		.hcxt = CurrentMemoryContext,
	};

	ctx->htab = hash_create("chunk-scan-context", 20, &hctl, HASH_ELEM | HASH_CONTEXT | HASH_BLOBS);
	ctx->space = hs;
	ctx->point = p;
	ctx->num_complete_chunks = 0;
	ctx->early_abort = false;
	ctx->lockmode = NoLock;
}