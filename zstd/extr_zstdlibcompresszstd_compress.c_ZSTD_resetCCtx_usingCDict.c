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
typedef  int /*<<< orphan*/  ZSTD_buffered_policy_e ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  scalar_t__ U64 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 size_t ZSTD_resetCCtx_byAttachingCDict (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t ZSTD_resetCCtx_byCopyingCDict (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_shouldAttachDict (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static size_t ZSTD_resetCCtx_usingCDict(ZSTD_CCtx* cctx,
                            const ZSTD_CDict* cdict,
                            ZSTD_CCtx_params params,
                            U64 pledgedSrcSize,
                            ZSTD_buffered_policy_e zbuff)
{

    DEBUGLOG(4, "ZSTD_resetCCtx_usingCDict (pledgedSrcSize=%u)",
                (unsigned)pledgedSrcSize);

    if (ZSTD_shouldAttachDict(cdict, params, pledgedSrcSize)) {
        return ZSTD_resetCCtx_byAttachingCDict(
            cctx, cdict, params, pledgedSrcSize, zbuff);
    } else {
        return ZSTD_resetCCtx_byCopyingCDict(
            cctx, cdict, params, pledgedSrcSize, zbuff);
    }
}