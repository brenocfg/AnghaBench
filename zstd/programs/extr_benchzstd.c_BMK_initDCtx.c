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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_Z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_DCtx_loadDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_DCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_and_parameters ; 

__attribute__((used)) static void BMK_initDCtx(ZSTD_DCtx* dctx,
    const void* dictBuffer, size_t dictBufferSize) {
    CHECK_Z(ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters));
    CHECK_Z(ZSTD_DCtx_loadDictionary(dctx, dictBuffer, dictBufferSize));
}