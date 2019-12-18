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
struct TYPE_5__ {int strategy; scalar_t__ targetLength; scalar_t__ minMatch; scalar_t__ searchLog; scalar_t__ chainLog; scalar_t__ hashLog; scalar_t__ windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
struct TYPE_6__ {int nbWorkers; int ldmFlag; int ldmMinMatch; int ldmHashLog; int ldmBucketSizeLog; int ldmHashRateLog; scalar_t__ literalCompressionMode; } ;
typedef  TYPE_2__ BMK_advancedParams_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_Z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_loadDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_chainLog ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 int /*<<< orphan*/  ZSTD_c_enableLongDistanceMatching ; 
 int /*<<< orphan*/  ZSTD_c_hashLog ; 
 int /*<<< orphan*/  ZSTD_c_ldmBucketSizeLog ; 
 int /*<<< orphan*/  ZSTD_c_ldmHashLog ; 
 int /*<<< orphan*/  ZSTD_c_ldmHashRateLog ; 
 int /*<<< orphan*/  ZSTD_c_ldmMinMatch ; 
 int /*<<< orphan*/  ZSTD_c_literalCompressionMode ; 
 int /*<<< orphan*/  ZSTD_c_minMatch ; 
 int /*<<< orphan*/  ZSTD_c_nbWorkers ; 
 int /*<<< orphan*/  ZSTD_c_searchLog ; 
 int /*<<< orphan*/  ZSTD_c_strategy ; 
 int /*<<< orphan*/  ZSTD_c_targetLength ; 
 int /*<<< orphan*/  ZSTD_c_windowLog ; 
 int /*<<< orphan*/  ZSTD_reset_session_and_parameters ; 

__attribute__((used)) static void
BMK_initCCtx(ZSTD_CCtx* ctx,
            const void* dictBuffer, size_t dictBufferSize,
            int cLevel,
            const ZSTD_compressionParameters* comprParams,
            const BMK_advancedParams_t* adv)
{
    ZSTD_CCtx_reset(ctx, ZSTD_reset_session_and_parameters);
    if (adv->nbWorkers==1) {
        CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_nbWorkers, 0));
    } else {
        CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_nbWorkers, adv->nbWorkers));
    }
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_compressionLevel, cLevel));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_enableLongDistanceMatching, adv->ldmFlag));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_ldmMinMatch, adv->ldmMinMatch));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_ldmHashLog, adv->ldmHashLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_ldmBucketSizeLog, adv->ldmBucketSizeLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_ldmHashRateLog, adv->ldmHashRateLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_windowLog, (int)comprParams->windowLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_hashLog, (int)comprParams->hashLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_chainLog, (int)comprParams->chainLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_searchLog, (int)comprParams->searchLog));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_minMatch, (int)comprParams->minMatch));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_targetLength, (int)comprParams->targetLength));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_literalCompressionMode, (int)adv->literalCompressionMode));
    CHECK_Z(ZSTD_CCtx_setParameter(ctx, ZSTD_c_strategy, comprParams->strategy));
    CHECK_Z(ZSTD_CCtx_loadDictionary(ctx, dictBuffer, dictBufferSize));
}