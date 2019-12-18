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
typedef  int /*<<< orphan*/  ZSTD_cParameter ;
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_CCtxParams_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 size_t ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static size_t setCCtxParameter(ZSTD_CCtx* zc, ZSTD_CCtx_params* cctxParams,
                               ZSTD_cParameter param, unsigned value,
                               int useOpaqueAPI)
{
    if (useOpaqueAPI) {
        return ZSTD_CCtxParams_setParameter(cctxParams, param, value);
    } else {
        return ZSTD_CCtx_setParameter(zc, param, value);
    }
}