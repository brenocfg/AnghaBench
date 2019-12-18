#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_cwksp ;
typedef  int /*<<< orphan*/  ZSTD_compressedBlockState_t ;
struct TYPE_5__ {int /*<<< orphan*/ * nextCBlock; int /*<<< orphan*/ * prevCBlock; } ;
struct TYPE_6__ {size_t staticSize; int /*<<< orphan*/  bmi2; int /*<<< orphan*/  workspace; int /*<<< orphan*/ * entropyWorkspace; TYPE_1__ blockState; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int HUF_WORKSPACE_SIZE ; 
 int /*<<< orphan*/  ZSTD_cpuid () ; 
 int /*<<< orphan*/  ZSTD_cpuid_bmi2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_cwksp_check_available (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_cwksp_init (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  ZSTD_cwksp_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_cwksp_reserve_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

ZSTD_CCtx* ZSTD_initStaticCCtx(void *workspace, size_t workspaceSize)
{
    ZSTD_cwksp ws;
    ZSTD_CCtx* cctx;
    if (workspaceSize <= sizeof(ZSTD_CCtx)) return NULL;  /* minimum size */
    if ((size_t)workspace & 7) return NULL;  /* must be 8-aligned */
    ZSTD_cwksp_init(&ws, workspace, workspaceSize);

    cctx = (ZSTD_CCtx*)ZSTD_cwksp_reserve_object(&ws, sizeof(ZSTD_CCtx));
    if (cctx == NULL) {
        return NULL;
    }
    memset(cctx, 0, sizeof(ZSTD_CCtx));
    ZSTD_cwksp_move(&cctx->workspace, &ws);
    cctx->staticSize = workspaceSize;

    /* statically sized space. entropyWorkspace never moves (but prev/next block swap places) */
    if (!ZSTD_cwksp_check_available(&cctx->workspace, HUF_WORKSPACE_SIZE + 2 * sizeof(ZSTD_compressedBlockState_t))) return NULL;
    cctx->blockState.prevCBlock = (ZSTD_compressedBlockState_t*)ZSTD_cwksp_reserve_object(&cctx->workspace, sizeof(ZSTD_compressedBlockState_t));
    cctx->blockState.nextCBlock = (ZSTD_compressedBlockState_t*)ZSTD_cwksp_reserve_object(&cctx->workspace, sizeof(ZSTD_compressedBlockState_t));
    cctx->entropyWorkspace = (U32*)ZSTD_cwksp_reserve_object(
        &cctx->workspace, HUF_WORKSPACE_SIZE);
    cctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
    return cctx;
}