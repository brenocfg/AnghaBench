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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_5__ {int /*<<< orphan*/  bmi2; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_CCtx_resetParameters (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_cpuid () ; 
 int /*<<< orphan*/  ZSTD_cpuid_bmi2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ZSTD_initCCtx(ZSTD_CCtx* cctx, ZSTD_customMem memManager)
{
    assert(cctx != NULL);
    memset(cctx, 0, sizeof(*cctx));
    cctx->customMem = memManager;
    cctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
    {   size_t const err = ZSTD_CCtx_resetParameters(cctx);
        assert(!ZSTD_isError(err));
        (void)err;
    }
}