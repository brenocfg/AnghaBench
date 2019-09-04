#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int member_0; int contentSizeFlag; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_buffered_policy_e ;
struct TYPE_9__ {scalar_t__ inBuffSize; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 size_t ZSTD_copyCCtx_internal (TYPE_2__*,TYPE_2__ const*,TYPE_1__,unsigned long long,int /*<<< orphan*/  const) ; 
 scalar_t__ ZSTDb_buffered ; 

size_t ZSTD_copyCCtx(ZSTD_CCtx* dstCCtx, const ZSTD_CCtx* srcCCtx, unsigned long long pledgedSrcSize)
{
    ZSTD_frameParameters fParams = { 1 /*content*/, 0 /*checksum*/, 0 /*noDictID*/ };
    ZSTD_buffered_policy_e const zbuff = (ZSTD_buffered_policy_e)(srcCCtx->inBuffSize>0);
    ZSTD_STATIC_ASSERT((U32)ZSTDb_buffered==1);
    if (pledgedSrcSize==0) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    fParams.contentSizeFlag = (pledgedSrcSize != ZSTD_CONTENTSIZE_UNKNOWN);

    return ZSTD_copyCCtx_internal(dstCCtx, srcCCtx,
                                fParams, pledgedSrcSize,
                                zbuff);
}