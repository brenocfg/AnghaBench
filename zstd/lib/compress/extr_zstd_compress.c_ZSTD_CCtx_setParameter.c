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
typedef  int ZSTD_cParameter ;
struct TYPE_3__ {scalar_t__ streamStage; int cParamsChanged; int /*<<< orphan*/  requestedParams; int /*<<< orphan*/  staticSize; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int,int) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,char*) ; 
 size_t ZSTD_CCtxParams_setParameter (int /*<<< orphan*/ *,int,int) ; 
#define  ZSTD_c_chainLog 153 
#define  ZSTD_c_checksumFlag 152 
#define  ZSTD_c_compressionLevel 151 
#define  ZSTD_c_contentSizeFlag 150 
#define  ZSTD_c_dictIDFlag 149 
#define  ZSTD_c_enableLongDistanceMatching 148 
#define  ZSTD_c_forceAttachDict 147 
#define  ZSTD_c_forceMaxWindow 146 
#define  ZSTD_c_format 145 
#define  ZSTD_c_hashLog 144 
#define  ZSTD_c_jobSize 143 
#define  ZSTD_c_ldmBucketSizeLog 142 
#define  ZSTD_c_ldmHashLog 141 
#define  ZSTD_c_ldmHashRateLog 140 
#define  ZSTD_c_ldmMinMatch 139 
#define  ZSTD_c_literalCompressionMode 138 
#define  ZSTD_c_minMatch 137 
#define  ZSTD_c_nbWorkers 136 
#define  ZSTD_c_overlapLog 135 
#define  ZSTD_c_rsyncable 134 
#define  ZSTD_c_searchLog 133 
#define  ZSTD_c_srcSizeHint 132 
#define  ZSTD_c_strategy 131 
#define  ZSTD_c_targetCBlockSize 130 
#define  ZSTD_c_targetLength 129 
#define  ZSTD_c_windowLog 128 
 scalar_t__ ZSTD_isUpdateAuthorized (int) ; 
 int /*<<< orphan*/  parameter_unsupported ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_setParameter(ZSTD_CCtx* cctx, ZSTD_cParameter param, int value)
{
    DEBUGLOG(4, "ZSTD_CCtx_setParameter (%i, %i)", (int)param, value);
    if (cctx->streamStage != zcss_init) {
        if (ZSTD_isUpdateAuthorized(param)) {
            cctx->cParamsChanged = 1;
        } else {
            RETURN_ERROR(stage_wrong);
    }   }

    switch(param)
    {
    case ZSTD_c_nbWorkers:
        RETURN_ERROR_IF((value!=0) && cctx->staticSize, parameter_unsupported,
                        "MT not compatible with static alloc");
        break;

    case ZSTD_c_compressionLevel:
    case ZSTD_c_windowLog:
    case ZSTD_c_hashLog:
    case ZSTD_c_chainLog:
    case ZSTD_c_searchLog:
    case ZSTD_c_minMatch:
    case ZSTD_c_targetLength:
    case ZSTD_c_strategy:
    case ZSTD_c_ldmHashRateLog:
    case ZSTD_c_format:
    case ZSTD_c_contentSizeFlag:
    case ZSTD_c_checksumFlag:
    case ZSTD_c_dictIDFlag:
    case ZSTD_c_forceMaxWindow:
    case ZSTD_c_forceAttachDict:
    case ZSTD_c_literalCompressionMode:
    case ZSTD_c_jobSize:
    case ZSTD_c_overlapLog:
    case ZSTD_c_rsyncable:
    case ZSTD_c_enableLongDistanceMatching:
    case ZSTD_c_ldmHashLog:
    case ZSTD_c_ldmMinMatch:
    case ZSTD_c_ldmBucketSizeLog:
    case ZSTD_c_targetCBlockSize:
    case ZSTD_c_srcSizeHint:
        break;

    default: RETURN_ERROR(parameter_unsupported);
    }
    return ZSTD_CCtxParams_setParameter(&cctx->requestedParams, param, value);
}