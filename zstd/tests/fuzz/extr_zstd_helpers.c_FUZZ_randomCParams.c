#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* strategy; void* targetLength; void* minMatch; void* searchLog; void* chainLog; void* hashLog; void* windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 void* FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_CHAINLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_HASHLOG_MIN ; 
 int ZSTD_MINMATCH_MAX ; 
 int /*<<< orphan*/  ZSTD_MINMATCH_MIN ; 
 int /*<<< orphan*/  ZSTD_SEARCHLOG_MIN ; 
 int ZSTD_STRATEGY_MAX ; 
 int /*<<< orphan*/  ZSTD_STRATEGY_MIN ; 
 int /*<<< orphan*/  ZSTD_WINDOWLOG_MIN ; 
 TYPE_1__ ZSTD_adjustCParams (TYPE_1__,size_t,int /*<<< orphan*/ ) ; 

ZSTD_compressionParameters FUZZ_randomCParams(size_t srcSize, FUZZ_dataProducer_t *producer)
{
    /* Select compression parameters */
    ZSTD_compressionParameters cParams;
    cParams.windowLog = FUZZ_dataProducer_uint32Range(producer, ZSTD_WINDOWLOG_MIN, 15);
    cParams.hashLog = FUZZ_dataProducer_uint32Range(producer, ZSTD_HASHLOG_MIN, 15);
    cParams.chainLog = FUZZ_dataProducer_uint32Range(producer, ZSTD_CHAINLOG_MIN, 16);
    cParams.searchLog = FUZZ_dataProducer_uint32Range(producer, ZSTD_SEARCHLOG_MIN, 9);
    cParams.minMatch = FUZZ_dataProducer_uint32Range(producer, ZSTD_MINMATCH_MIN,
                                          ZSTD_MINMATCH_MAX);
    cParams.targetLength = FUZZ_dataProducer_uint32Range(producer, 0, 512);
    cParams.strategy = FUZZ_dataProducer_uint32Range(producer, ZSTD_STRATEGY_MIN, ZSTD_STRATEGY_MAX);
    return ZSTD_adjustCParams(cParams, srcSize, 0);
}