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
typedef  int ZSTD_DStreamParameter_e ;
struct TYPE_3__ {scalar_t__ streamStage; unsigned int maxWindowSize; } ;
typedef  TYPE_1__ ZSTD_DStream ;
typedef  unsigned int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
#define  DStream_p_maxWindowSize 128 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parameter_unsupported ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zdss_init ; 

size_t ZSTD_setDStreamParameter(ZSTD_DStream* dctx,
                                ZSTD_DStreamParameter_e paramType, unsigned paramValue)
{
    if (dctx->streamStage != zdss_init) return ERROR(stage_wrong);
    switch(paramType)
    {
        default : return ERROR(parameter_unsupported);
        case DStream_p_maxWindowSize :
            DEBUGLOG(4, "setting maxWindowSize = %u KB", paramValue >> 10);
            dctx->maxWindowSize = paramValue ? paramValue : (U32)(-1);
            break;
    }
    return 0;
}