#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void ZSTD_compressedBlockState_t ;
struct TYPE_4__ {void* prevCBlock; void* nextCBlock; } ;
struct TYPE_5__ {size_t staticSize; size_t workSpaceSize; int /*<<< orphan*/  bmi2; int /*<<< orphan*/ * entropyWorkspace; TYPE_1__ blockState; void* workSpace; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int HUF_WORKSPACE_SIZE ; 
 int /*<<< orphan*/  ZSTD_cpuid () ; 
 int /*<<< orphan*/  ZSTD_cpuid_bmi2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

ZSTD_CCtx* ZSTD_initStaticCCtx(void *workspace, size_t workspaceSize)
{
    ZSTD_CCtx* const cctx = (ZSTD_CCtx*) workspace;
    if (workspaceSize <= sizeof(ZSTD_CCtx)) return NULL;  /* minimum size */
    if ((size_t)workspace & 7) return NULL;  /* must be 8-aligned */
    memset(workspace, 0, workspaceSize);   /* may be a bit generous, could memset be smaller ? */
    cctx->staticSize = workspaceSize;
    cctx->workSpace = (void*)(cctx+1);
    cctx->workSpaceSize = workspaceSize - sizeof(ZSTD_CCtx);

    /* statically sized space. entropyWorkspace never moves (but prev/next block swap places) */
    if (cctx->workSpaceSize < HUF_WORKSPACE_SIZE + 2 * sizeof(ZSTD_compressedBlockState_t)) return NULL;
    assert(((size_t)cctx->workSpace & (sizeof(void*)-1)) == 0);   /* ensure correct alignment */
    cctx->blockState.prevCBlock = (ZSTD_compressedBlockState_t*)cctx->workSpace;
    cctx->blockState.nextCBlock = cctx->blockState.prevCBlock + 1;
    {
        void* const ptr = cctx->blockState.nextCBlock + 1;
        cctx->entropyWorkspace = (U32*)ptr;
    }
    cctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
    return cctx;
}