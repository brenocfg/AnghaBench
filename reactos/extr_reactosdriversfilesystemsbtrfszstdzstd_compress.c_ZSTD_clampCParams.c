#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ windowLog; scalar_t__ chainLog; scalar_t__ hashLog; scalar_t__ searchLog; scalar_t__ searchLength; scalar_t__ targetLength; scalar_t__ strategy; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;

/* Variables and functions */
 scalar_t__ ZSTD_CHAINLOG_MAX ; 
 scalar_t__ ZSTD_CHAINLOG_MIN ; 
 scalar_t__ ZSTD_HASHLOG_MAX ; 
 scalar_t__ ZSTD_HASHLOG_MIN ; 
 scalar_t__ ZSTD_SEARCHLENGTH_MAX ; 
 scalar_t__ ZSTD_SEARCHLENGTH_MIN ; 
 scalar_t__ ZSTD_SEARCHLOG_MAX ; 
 scalar_t__ ZSTD_SEARCHLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 scalar_t__ ZSTD_TARGETLENGTH_MAX ; 
 scalar_t__ ZSTD_TARGETLENGTH_MIN ; 
 scalar_t__ ZSTD_WINDOWLOG_MAX ; 
 scalar_t__ ZSTD_WINDOWLOG_MIN ; 
 scalar_t__ ZSTD_btultra ; 
 scalar_t__ ZSTD_fast ; 

__attribute__((used)) static ZSTD_compressionParameters
ZSTD_clampCParams(ZSTD_compressionParameters cParams)
{
#   define CLAMP(val,min,max) {      \
        if (val<min) val=min;        \
        else if (val>max) val=max;   \
    }
    CLAMP(cParams.windowLog, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
    CLAMP(cParams.chainLog, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
    CLAMP(cParams.hashLog, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
    CLAMP(cParams.searchLog, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
    CLAMP(cParams.searchLength, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
    ZSTD_STATIC_ASSERT(ZSTD_TARGETLENGTH_MIN == 0);
    if (cParams.targetLength > ZSTD_TARGETLENGTH_MAX)
        cParams.targetLength = ZSTD_TARGETLENGTH_MAX;
    CLAMP(cParams.strategy, ZSTD_fast, ZSTD_btultra);
    return cParams;
}