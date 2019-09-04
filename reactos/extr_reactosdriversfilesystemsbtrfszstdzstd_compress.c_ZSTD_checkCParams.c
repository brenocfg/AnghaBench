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
struct TYPE_3__ {scalar_t__ targetLength; scalar_t__ strategy; int /*<<< orphan*/  searchLength; int /*<<< orphan*/  searchLog; int /*<<< orphan*/  hashLog; int /*<<< orphan*/  chainLog; int /*<<< orphan*/  windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMPCHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CHAINLOG_MAX ; 
 int /*<<< orphan*/  ZSTD_CHAINLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_HASHLOG_MAX ; 
 int /*<<< orphan*/  ZSTD_HASHLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_SEARCHLENGTH_MAX ; 
 int /*<<< orphan*/  ZSTD_SEARCHLENGTH_MIN ; 
 int /*<<< orphan*/  ZSTD_SEARCHLOG_MAX ; 
 int /*<<< orphan*/  ZSTD_SEARCHLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 scalar_t__ ZSTD_TARGETLENGTH_MAX ; 
 scalar_t__ ZSTD_TARGETLENGTH_MIN ; 
 int /*<<< orphan*/  ZSTD_WINDOWLOG_MAX ; 
 int /*<<< orphan*/  ZSTD_WINDOWLOG_MIN ; 
 scalar_t__ ZSTD_btultra ; 
 int /*<<< orphan*/  parameter_outOfBound ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_checkCParams(ZSTD_compressionParameters cParams)
{
    CLAMPCHECK(cParams.windowLog, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
    CLAMPCHECK(cParams.chainLog, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
    CLAMPCHECK(cParams.hashLog, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
    CLAMPCHECK(cParams.searchLog, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
    CLAMPCHECK(cParams.searchLength, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
    ZSTD_STATIC_ASSERT(ZSTD_TARGETLENGTH_MIN == 0);
    if (cParams.targetLength > ZSTD_TARGETLENGTH_MAX)
        return ERROR(parameter_outOfBound);
    if ((U32)(cParams.strategy) > (U32)ZSTD_btultra)
        return ERROR(parameter_unsupported);
    return 0;
}