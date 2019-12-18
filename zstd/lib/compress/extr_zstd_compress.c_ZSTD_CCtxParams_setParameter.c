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
typedef  int /*<<< orphan*/  ZSTD_strategy ;
typedef  int ZSTD_literalCompressionMode_e ;
typedef  int /*<<< orphan*/  ZSTD_format_e ;
typedef  int ZSTD_dictAttachPref_e ;
typedef  int ZSTD_cParameter ;
struct TYPE_8__ {int enableLdm; int hashLog; int minMatchLength; int bucketSizeLog; int hashRateLog; } ;
struct TYPE_7__ {int contentSizeFlag; int checksumFlag; int noDictIDFlag; } ;
struct TYPE_6__ {size_t windowLog; size_t hashLog; size_t chainLog; int minMatch; int targetLength; int /*<<< orphan*/  strategy; void* searchLog; } ;
struct TYPE_9__ {int compressionLevel; int forceWindow; int attachDictPref; int literalCompressionMode; int nbWorkers; int jobSize; int overlapLog; int rsyncable; int targetCBlockSize; int srcSizeHint; TYPE_3__ ldmParams; TYPE_2__ fParams; TYPE_1__ cParams; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ ZSTD_CCtx_params ;
typedef  void* U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNDCHECK (int const,int const) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int,...) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,...) ; 
 int ZSTDMT_JOBSIZE_MIN ; 
 int ZSTD_HASHLOG_MIN ; 
 int ZSTD_WINDOWLOG_MAX ; 
 int /*<<< orphan*/  ZSTD_cParam_clampBounds (int const,int*) ; 
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
 int /*<<< orphan*/  parameter_outOfBound ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_CCtxParams_setParameter(ZSTD_CCtx_params* CCtxParams,
                                    ZSTD_cParameter param, int value)
{
    DEBUGLOG(4, "ZSTD_CCtxParams_setParameter (%i, %i)", (int)param, value);
    switch(param)
    {
    case ZSTD_c_format :
        BOUNDCHECK(ZSTD_c_format, value);
        CCtxParams->format = (ZSTD_format_e)value;
        return (size_t)CCtxParams->format;

    case ZSTD_c_compressionLevel : {
        FORWARD_IF_ERROR(ZSTD_cParam_clampBounds(param, &value));
        if (value) {  /* 0 : does not change current level */
            CCtxParams->compressionLevel = value;
        }
        if (CCtxParams->compressionLevel >= 0) return (size_t)CCtxParams->compressionLevel;
        return 0;  /* return type (size_t) cannot represent negative values */
    }

    case ZSTD_c_windowLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_windowLog, value);
        CCtxParams->cParams.windowLog = (U32)value;
        return CCtxParams->cParams.windowLog;

    case ZSTD_c_hashLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_hashLog, value);
        CCtxParams->cParams.hashLog = (U32)value;
        return CCtxParams->cParams.hashLog;

    case ZSTD_c_chainLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_chainLog, value);
        CCtxParams->cParams.chainLog = (U32)value;
        return CCtxParams->cParams.chainLog;

    case ZSTD_c_searchLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_searchLog, value);
        CCtxParams->cParams.searchLog = (U32)value;
        return (size_t)value;

    case ZSTD_c_minMatch :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_minMatch, value);
        CCtxParams->cParams.minMatch = value;
        return CCtxParams->cParams.minMatch;

    case ZSTD_c_targetLength :
        BOUNDCHECK(ZSTD_c_targetLength, value);
        CCtxParams->cParams.targetLength = value;
        return CCtxParams->cParams.targetLength;

    case ZSTD_c_strategy :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_strategy, value);
        CCtxParams->cParams.strategy = (ZSTD_strategy)value;
        return (size_t)CCtxParams->cParams.strategy;

    case ZSTD_c_contentSizeFlag :
        /* Content size written in frame header _when known_ (default:1) */
        DEBUGLOG(4, "set content size flag = %u", (value!=0));
        CCtxParams->fParams.contentSizeFlag = value != 0;
        return CCtxParams->fParams.contentSizeFlag;

    case ZSTD_c_checksumFlag :
        /* A 32-bits content checksum will be calculated and written at end of frame (default:0) */
        CCtxParams->fParams.checksumFlag = value != 0;
        return CCtxParams->fParams.checksumFlag;

    case ZSTD_c_dictIDFlag : /* When applicable, dictionary's dictID is provided in frame header (default:1) */
        DEBUGLOG(4, "set dictIDFlag = %u", (value!=0));
        CCtxParams->fParams.noDictIDFlag = !value;
        return !CCtxParams->fParams.noDictIDFlag;

    case ZSTD_c_forceMaxWindow :
        CCtxParams->forceWindow = (value != 0);
        return CCtxParams->forceWindow;

    case ZSTD_c_forceAttachDict : {
        const ZSTD_dictAttachPref_e pref = (ZSTD_dictAttachPref_e)value;
        BOUNDCHECK(ZSTD_c_forceAttachDict, pref);
        CCtxParams->attachDictPref = pref;
        return CCtxParams->attachDictPref;
    }

    case ZSTD_c_literalCompressionMode : {
        const ZSTD_literalCompressionMode_e lcm = (ZSTD_literalCompressionMode_e)value;
        BOUNDCHECK(ZSTD_c_literalCompressionMode, lcm);
        CCtxParams->literalCompressionMode = lcm;
        return CCtxParams->literalCompressionMode;
    }

    case ZSTD_c_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR_IF(value!=0, parameter_unsupported, "not compiled with multithreading");
        return 0;
#else
        FORWARD_IF_ERROR(ZSTD_cParam_clampBounds(param, &value));
        CCtxParams->nbWorkers = value;
        return CCtxParams->nbWorkers;
#endif

    case ZSTD_c_jobSize :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR_IF(value!=0, parameter_unsupported, "not compiled with multithreading");
        return 0;
#else
        /* Adjust to the minimum non-default value. */
        if (value != 0 && value < ZSTDMT_JOBSIZE_MIN)
            value = ZSTDMT_JOBSIZE_MIN;
        FORWARD_IF_ERROR(ZSTD_cParam_clampBounds(param, &value));
        assert(value >= 0);
        CCtxParams->jobSize = value;
        return CCtxParams->jobSize;
#endif

    case ZSTD_c_overlapLog :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR_IF(value!=0, parameter_unsupported, "not compiled with multithreading");
        return 0;
#else
        FORWARD_IF_ERROR(ZSTD_cParam_clampBounds(ZSTD_c_overlapLog, &value));
        CCtxParams->overlapLog = value;
        return CCtxParams->overlapLog;
#endif

    case ZSTD_c_rsyncable :
#ifndef ZSTD_MULTITHREAD
        RETURN_ERROR_IF(value!=0, parameter_unsupported, "not compiled with multithreading");
        return 0;
#else
        FORWARD_IF_ERROR(ZSTD_cParam_clampBounds(ZSTD_c_overlapLog, &value));
        CCtxParams->rsyncable = value;
        return CCtxParams->rsyncable;
#endif

    case ZSTD_c_enableLongDistanceMatching :
        CCtxParams->ldmParams.enableLdm = (value!=0);
        return CCtxParams->ldmParams.enableLdm;

    case ZSTD_c_ldmHashLog :
        if (value!=0)   /* 0 ==> auto */
            BOUNDCHECK(ZSTD_c_ldmHashLog, value);
        CCtxParams->ldmParams.hashLog = value;
        return CCtxParams->ldmParams.hashLog;

    case ZSTD_c_ldmMinMatch :
        if (value!=0)   /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_ldmMinMatch, value);
        CCtxParams->ldmParams.minMatchLength = value;
        return CCtxParams->ldmParams.minMatchLength;

    case ZSTD_c_ldmBucketSizeLog :
        if (value!=0)   /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_ldmBucketSizeLog, value);
        CCtxParams->ldmParams.bucketSizeLog = value;
        return CCtxParams->ldmParams.bucketSizeLog;

    case ZSTD_c_ldmHashRateLog :
        RETURN_ERROR_IF(value > ZSTD_WINDOWLOG_MAX - ZSTD_HASHLOG_MIN,
                        parameter_outOfBound);
        CCtxParams->ldmParams.hashRateLog = value;
        return CCtxParams->ldmParams.hashRateLog;

    case ZSTD_c_targetCBlockSize :
        if (value!=0)   /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_targetCBlockSize, value);
        CCtxParams->targetCBlockSize = value;
        return CCtxParams->targetCBlockSize;

    case ZSTD_c_srcSizeHint :
        if (value!=0)    /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_srcSizeHint, value);
        CCtxParams->srcSizeHint = value;
        return CCtxParams->srcSizeHint;

    default: RETURN_ERROR(parameter_unsupported, "unknown parameter");
    }
}