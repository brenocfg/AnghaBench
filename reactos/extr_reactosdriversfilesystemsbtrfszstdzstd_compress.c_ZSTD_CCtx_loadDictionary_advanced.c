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
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
struct TYPE_3__ {scalar_t__ streamStage; int /*<<< orphan*/ * cdictLocal; int /*<<< orphan*/ * cdict; int /*<<< orphan*/  customMem; scalar_t__ pledgedSrcSizePlusOne; int /*<<< orphan*/  requestedParams; scalar_t__ staticSize; } ;
typedef  TYPE_1__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTD_createCDict_advanced (void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_getCParamsFromCCtxParams (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memory_allocation ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_loadDictionary_advanced(
        ZSTD_CCtx* cctx, const void* dict, size_t dictSize,
        ZSTD_dictLoadMethod_e dictLoadMethod, ZSTD_dictContentType_e dictContentType)
{
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    if (cctx->staticSize) return ERROR(memory_allocation);  /* no malloc for static CCtx */
    DEBUGLOG(4, "ZSTD_CCtx_loadDictionary_advanced (size: %u)", (U32)dictSize);
    ZSTD_freeCDict(cctx->cdictLocal);  /* in case one already exists */
    if (dict==NULL || dictSize==0) {   /* no dictionary mode */
        cctx->cdictLocal = NULL;
        cctx->cdict = NULL;
    } else {
        ZSTD_compressionParameters const cParams =
                ZSTD_getCParamsFromCCtxParams(&cctx->requestedParams, cctx->pledgedSrcSizePlusOne-1, dictSize);
        cctx->cdictLocal = ZSTD_createCDict_advanced(
                                dict, dictSize,
                                dictLoadMethod, dictContentType,
                                cParams, cctx->customMem);
        cctx->cdict = cctx->cdictLocal;
        if (cctx->cdictLocal == NULL)
            return ERROR(memory_allocation);
    }
    return 0;
}