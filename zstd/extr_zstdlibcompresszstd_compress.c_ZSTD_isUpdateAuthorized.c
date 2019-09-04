#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ZSTD_cParameter ;

/* Variables and functions */
#define  ZSTD_c_chainLog 151 
#define  ZSTD_c_checksumFlag 150 
#define  ZSTD_c_compressionLevel 149 
#define  ZSTD_c_contentSizeFlag 148 
#define  ZSTD_c_dictIDFlag 147 
#define  ZSTD_c_enableLongDistanceMatching 146 
#define  ZSTD_c_forceAttachDict 145 
#define  ZSTD_c_forceMaxWindow 144 
#define  ZSTD_c_format 143 
#define  ZSTD_c_hashLog 142 
#define  ZSTD_c_jobSize 141 
#define  ZSTD_c_ldmBucketSizeLog 140 
#define  ZSTD_c_ldmHashLog 139 
#define  ZSTD_c_ldmHashRateLog 138 
#define  ZSTD_c_ldmMinMatch 137 
#define  ZSTD_c_literalCompressionMode 136 
#define  ZSTD_c_minMatch 135 
#define  ZSTD_c_nbWorkers 134 
#define  ZSTD_c_overlapLog 133 
#define  ZSTD_c_rsyncable 132 
#define  ZSTD_c_searchLog 131 
#define  ZSTD_c_strategy 130 
#define  ZSTD_c_targetLength 129 
#define  ZSTD_c_windowLog 128 

__attribute__((used)) static int ZSTD_isUpdateAuthorized(ZSTD_cParameter param)
{
    switch(param)
    {
    case ZSTD_c_compressionLevel:
    case ZSTD_c_hashLog:
    case ZSTD_c_chainLog:
    case ZSTD_c_searchLog:
    case ZSTD_c_minMatch:
    case ZSTD_c_targetLength:
    case ZSTD_c_strategy:
        return 1;

    case ZSTD_c_format:
    case ZSTD_c_windowLog:
    case ZSTD_c_contentSizeFlag:
    case ZSTD_c_checksumFlag:
    case ZSTD_c_dictIDFlag:
    case ZSTD_c_forceMaxWindow :
    case ZSTD_c_nbWorkers:
    case ZSTD_c_jobSize:
    case ZSTD_c_overlapLog:
    case ZSTD_c_rsyncable:
    case ZSTD_c_enableLongDistanceMatching:
    case ZSTD_c_ldmHashLog:
    case ZSTD_c_ldmMinMatch:
    case ZSTD_c_ldmBucketSizeLog:
    case ZSTD_c_ldmHashRateLog:
    case ZSTD_c_forceAttachDict:
    case ZSTD_c_literalCompressionMode:
    default:
        return 0;
    }
}