#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ contentSizeFlag; } ;
struct TYPE_8__ {TYPE_1__ fParams; } ;
struct TYPE_9__ {scalar_t__ pledgedSrcSizePlusOne; scalar_t__ consumedSrcSize; TYPE_2__ appliedParams; } ;
typedef  TYPE_3__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (size_t const) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 size_t ZSTD_compressContinue_internal (TYPE_3__*,void*,size_t,void const*,size_t,int,int) ; 
 size_t ZSTD_writeEpilogue (TYPE_3__*,char*,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_compressEnd (ZSTD_CCtx* cctx,
                         void* dst, size_t dstCapacity,
                   const void* src, size_t srcSize)
{
    size_t endResult;
    size_t const cSize = ZSTD_compressContinue_internal(cctx,
                                dst, dstCapacity, src, srcSize,
                                1 /* frame mode */, 1 /* last chunk */);
    FORWARD_IF_ERROR(cSize);
    endResult = ZSTD_writeEpilogue(cctx, (char*)dst + cSize, dstCapacity-cSize);
    FORWARD_IF_ERROR(endResult);
    assert(!(cctx->appliedParams.fParams.contentSizeFlag && cctx->pledgedSrcSizePlusOne == 0));
    if (cctx->pledgedSrcSizePlusOne != 0) {  /* control src size */
        ZSTD_STATIC_ASSERT(ZSTD_CONTENTSIZE_UNKNOWN == (unsigned long long)-1);
        DEBUGLOG(4, "end of frame : controlling src size");
        RETURN_ERROR_IF(
            cctx->pledgedSrcSizePlusOne != cctx->consumedSrcSize+1,
            srcSize_wrong,
             "error : pledgedSrcSize = %u, while realSrcSize = %u",
            (unsigned)cctx->pledgedSrcSizePlusOne-1,
            (unsigned)cctx->consumedSrcSize);
    }
    return cSize + endResult;
}