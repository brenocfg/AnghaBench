#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictTableLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_buffered_policy_e ;
struct TYPE_17__ {scalar_t__ dictContentSize; } ;
typedef  TYPE_2__ ZSTD_CDict ;
struct TYPE_15__ {int /*<<< orphan*/  windowLog; } ;
struct TYPE_18__ {TYPE_14__ cParams; } ;
typedef  TYPE_3__ ZSTD_CCtx_params ;
struct TYPE_16__ {int /*<<< orphan*/  matchState; int /*<<< orphan*/  prevCBlock; } ;
struct TYPE_19__ {scalar_t__ dictID; int /*<<< orphan*/  entropyWorkspace; TYPE_1__ blockState; } ;
typedef  TYPE_4__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U64 ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 size_t const ZSTD_checkCParams (TYPE_14__) ; 
 size_t ZSTD_compress_insertDictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  ZSTD_resetCCtx_internal (TYPE_4__*,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ZSTD_resetCCtx_usingCDict (TYPE_4__*,TYPE_2__ const*,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDcrp_continue ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t ZSTD_compressBegin_internal(ZSTD_CCtx* cctx,
                                    const void* dict, size_t dictSize,
                                    ZSTD_dictContentType_e dictContentType,
                                    ZSTD_dictTableLoadMethod_e dtlm,
                                    const ZSTD_CDict* cdict,
                                    ZSTD_CCtx_params params, U64 pledgedSrcSize,
                                    ZSTD_buffered_policy_e zbuff)
{
    DEBUGLOG(4, "ZSTD_compressBegin_internal: wlog=%u", params.cParams.windowLog);
    /* params are supposed to be fully validated at this point */
    assert(!ZSTD_isError(ZSTD_checkCParams(params.cParams)));
    assert(!((dict) && (cdict)));  /* either dict or cdict, not both */

    if (cdict && cdict->dictContentSize>0) {
        return ZSTD_resetCCtx_usingCDict(cctx, cdict, params, pledgedSrcSize, zbuff);
    }

    CHECK_F( ZSTD_resetCCtx_internal(cctx, params, pledgedSrcSize,
                                     ZSTDcrp_continue, zbuff) );
    {
        size_t const dictID = ZSTD_compress_insertDictionary(
                cctx->blockState.prevCBlock, &cctx->blockState.matchState,
                &params, dict, dictSize, dictContentType, dtlm, cctx->entropyWorkspace);
        if (ZSTD_isError(dictID)) return dictID;
        assert(dictID <= (size_t)(U32)-1);
        cctx->dictID = (U32)dictID;
    }
    return 0;
}