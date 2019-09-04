#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dictBufferSize; int /*<<< orphan*/  dictBuffer; int /*<<< orphan*/  dctx; } ;
typedef  TYPE_1__ BMK_initDCtxArgs ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_DCtx_loadDictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_DCtx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_and_parameters ; 

__attribute__((used)) static size_t local_initDCtx(void* payload) {
    const BMK_initDCtxArgs* ag = (const BMK_initDCtxArgs*)payload;
    ZSTD_DCtx_reset(ag->dctx, ZSTD_reset_session_and_parameters);
    ZSTD_DCtx_loadDictionary(ag->dctx, ag->dictBuffer, ag->dictBufferSize);
    return 0;
}