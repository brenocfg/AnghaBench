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
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;

/* Variables and functions */
 size_t ZSTD_CCtxParams_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CLEVEL_DEFAULT ; 

size_t ZSTD_CCtxParams_reset(ZSTD_CCtx_params* params)
{
    return ZSTD_CCtxParams_init(params, ZSTD_CLEVEL_DEFAULT);
}