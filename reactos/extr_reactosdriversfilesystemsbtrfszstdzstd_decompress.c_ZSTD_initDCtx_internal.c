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
struct TYPE_3__ {int /*<<< orphan*/  bmi2; scalar_t__ noForwardProgress; scalar_t__ previousLegacyVersion; int /*<<< orphan*/ * legacyContext; int /*<<< orphan*/  streamStage; scalar_t__ outBuffSize; scalar_t__ inBuffSize; int /*<<< orphan*/ * inBuff; scalar_t__ ddictIsCold; int /*<<< orphan*/ * dictEnd; int /*<<< orphan*/ * ddictLocal; int /*<<< orphan*/ * ddict; int /*<<< orphan*/  maxWindowSize; scalar_t__ staticSize; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_MAXWINDOWSIZE_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_cpuid () ; 
 int /*<<< orphan*/  ZSTD_cpuid_bmi2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_f_zstd1 ; 
 int /*<<< orphan*/  zdss_init ; 

__attribute__((used)) static void ZSTD_initDCtx_internal(ZSTD_DCtx* dctx)
{
    dctx->format = ZSTD_f_zstd1;  /* ZSTD_decompressBegin() invokes ZSTD_startingInputLength() with argument dctx->format */
    dctx->staticSize  = 0;
    dctx->maxWindowSize = ZSTD_MAXWINDOWSIZE_DEFAULT;
    dctx->ddict       = NULL;
    dctx->ddictLocal  = NULL;
    dctx->dictEnd     = NULL;
    dctx->ddictIsCold = 0;
    dctx->inBuff      = NULL;
    dctx->inBuffSize  = 0;
    dctx->outBuffSize = 0;
    dctx->streamStage = zdss_init;
    dctx->legacyContext = NULL;
    dctx->previousLegacyVersion = 0;
    dctx->noForwardProgress = 0;
    dctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
}