#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ZSTD_cParameter ;
struct TYPE_8__ {int enableLdm; int hashLog; int minMatchLength; int bucketSizeLog; int hashRateLog; } ;
struct TYPE_7__ {int contentSizeFlag; int checksumFlag; int /*<<< orphan*/  noDictIDFlag; } ;
struct TYPE_6__ {int searchLog; int minMatch; int targetLength; int /*<<< orphan*/  strategy; scalar_t__ chainLog; scalar_t__ hashLog; scalar_t__ windowLog; } ;
struct TYPE_9__ {int format; int compressionLevel; int forceWindow; int attachDictPref; int literalCompressionMode; int nbWorkers; int overlapLog; int rsyncable; scalar_t__ srcSizeHint; scalar_t__ targetCBlockSize; TYPE_3__ ldmParams; scalar_t__ jobSize; TYPE_2__ fParams; TYPE_1__ cParams; } ;
typedef  TYPE_4__ ZSTD_CCtx_params ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,char*) ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_CCtxParams_getParameter(
        ZSTD_CCtx_params* CCtxParams, ZSTD_cParameter param, int* value)
{
    switch(param)
    {
    case ZSTD_c_format :
        *value = CCtxParams->format;
        break;
    case ZSTD_c_compressionLevel :
        *value = CCtxParams->compressionLevel;
        break;
    case ZSTD_c_windowLog :
        *value = (int)CCtxParams->cParams.windowLog;
        break;
    case ZSTD_c_hashLog :
        *value = (int)CCtxParams->cParams.hashLog;
        break;
    case ZSTD_c_chainLog :
        *value = (int)CCtxParams->cParams.chainLog;
        break;
    case ZSTD_c_searchLog :
        *value = CCtxParams->cParams.searchLog;
        break;
    case ZSTD_c_minMatch :
        *value = CCtxParams->cParams.minMatch;
        break;
    case ZSTD_c_targetLength :
        *value = CCtxParams->cParams.targetLength;
        break;
    case ZSTD_c_strategy :
        *value = (unsigned)CCtxParams->cParams.strategy;
        break;
    case ZSTD_c_contentSizeFlag :
        *value = CCtxParams->fParams.contentSizeFlag;
        break;
    case ZSTD_c_checksumFlag :
        *value = CCtxParams->fParams.checksumFlag;
        break;
    case ZSTD_c_dictIDFlag :
        *value = !CCtxParams->fParams.noDictIDFlag;
        break;
    case ZSTD_c_forceMaxWindow :
        *value = CCtxParams->forceWindow;
        break;
    case ZSTD_c_forceAttachDict :
        *value = CCtxParams->attachDictPref;
        break;
    case ZSTD_c_literalCompressionMode :
        *value = CCtxParams->literalCompressionMode;
        break;
    case ZSTD_c_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        assert(CCtxParams->nbWorkers == 0);
#endif
        *value = CCtxParams->nbWorkers;
        break;
    case ZSTD_c_jobSize :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR(parameter_unsupported, "not compiled with multithreading");
#else
        assert(CCtxParams->jobSize <= INT_MAX);
        *value = (int)CCtxParams->jobSize;
        break;
#endif
    case ZSTD_c_overlapLog :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR(parameter_unsupported, "not compiled with multithreading");
#else
        *value = CCtxParams->overlapLog;
        break;
#endif
    case ZSTD_c_rsyncable :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR(parameter_unsupported, "not compiled with multithreading");
#else
        *value = CCtxParams->rsyncable;
        break;
#endif
    case ZSTD_c_enableLongDistanceMatching :
        *value = CCtxParams->ldmParams.enableLdm;
        break;
    case ZSTD_c_ldmHashLog :
        *value = CCtxParams->ldmParams.hashLog;
        break;
    case ZSTD_c_ldmMinMatch :
        *value = CCtxParams->ldmParams.minMatchLength;
        break;
    case ZSTD_c_ldmBucketSizeLog :
        *value = CCtxParams->ldmParams.bucketSizeLog;
        break;
    case ZSTD_c_ldmHashRateLog :
        *value = CCtxParams->ldmParams.hashRateLog;
        break;
    case ZSTD_c_targetCBlockSize :
        *value = (int)CCtxParams->targetCBlockSize;
        break;
    case ZSTD_c_srcSizeHint :
        *value = (int)CCtxParams->srcSizeHint;
        break;
    default: RETURN_ERROR(parameter_unsupported, "unknown parameter");
    }
    return 0;
}