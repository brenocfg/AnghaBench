#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int blockType; } ;
typedef  TYPE_1__ blockProperties_t ;
struct TYPE_11__ {char const* dictEnd; char const* previousDstEnd; char const* vBase; char const* base; } ;
typedef  TYPE_2__ ZSTD_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t ZSTD_blockHeaderSize ; 
 size_t ZSTD_copyRawBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t) ; 
 size_t ZSTD_decodeFrameHeader_Part1 (TYPE_2__*,void const*,size_t) ; 
 size_t ZSTD_decodeFrameHeader_Part2 (TYPE_2__*,void const*,size_t) ; 
 size_t ZSTD_decompressBlock_internal (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_decompress_insertDictionary (TYPE_2__*,void const*,size_t) ; 
 size_t ZSTD_frameHeaderSize_min ; 
 size_t ZSTD_getcBlockSize (int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  ZSTD_resetDCtx (TYPE_2__*) ; 
#define  bt_compressed 131 
#define  bt_end 130 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_decompress_usingDict(ZSTD_DCtx* ctx,
                                 void* dst, size_t maxDstSize,
                                 const void* src, size_t srcSize,
                                 const void* dict, size_t dictSize)
{
    const BYTE* ip = (const BYTE*)src;
    const BYTE* iend = ip + srcSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + maxDstSize;
    size_t remainingSize = srcSize;
    blockProperties_t blockProperties;

    /* init */
    ZSTD_resetDCtx(ctx);
    if (dict)
    {
        ZSTD_decompress_insertDictionary(ctx, dict, dictSize);
        ctx->dictEnd = ctx->previousDstEnd;
        ctx->vBase = (const char*)dst - ((const char*)(ctx->previousDstEnd) - (const char*)(ctx->base));
        ctx->base = dst;
    }
    else
    {
        ctx->vBase = ctx->base = ctx->dictEnd = dst;
    }

    /* Frame Header */
    {
        size_t frameHeaderSize;
        if (srcSize < ZSTD_frameHeaderSize_min+ZSTD_blockHeaderSize) return ERROR(srcSize_wrong);
        frameHeaderSize = ZSTD_decodeFrameHeader_Part1(ctx, src, ZSTD_frameHeaderSize_min);
        if (ZSTD_isError(frameHeaderSize)) return frameHeaderSize;
        if (srcSize < frameHeaderSize+ZSTD_blockHeaderSize) return ERROR(srcSize_wrong);
        ip += frameHeaderSize; remainingSize -= frameHeaderSize;
        frameHeaderSize = ZSTD_decodeFrameHeader_Part2(ctx, src, frameHeaderSize);
        if (ZSTD_isError(frameHeaderSize)) return frameHeaderSize;
    }

    /* Loop on each block */
    while (1)
    {
        size_t decodedSize=0;
        size_t cBlockSize = ZSTD_getcBlockSize(ip, iend-ip, &blockProperties);
        if (ZSTD_isError(cBlockSize)) return cBlockSize;

        ip += ZSTD_blockHeaderSize;
        remainingSize -= ZSTD_blockHeaderSize;
        if (cBlockSize > remainingSize) return ERROR(srcSize_wrong);

        switch(blockProperties.blockType)
        {
        case bt_compressed:
            decodedSize = ZSTD_decompressBlock_internal(ctx, op, oend-op, ip, cBlockSize);
            break;
        case bt_raw :
            decodedSize = ZSTD_copyRawBlock(op, oend-op, ip, cBlockSize);
            break;
        case bt_rle :
            return ERROR(GENERIC);   /* not yet supported */
            break;
        case bt_end :
            /* end of frame */
            if (remainingSize) return ERROR(srcSize_wrong);
            break;
        default:
            return ERROR(GENERIC);   /* impossible */
        }
        if (cBlockSize == 0) break;   /* bt_end */

        if (ZSTD_isError(decodedSize)) return decodedSize;
        op += decodedSize;
        ip += cBlockSize;
        remainingSize -= cBlockSize;
    }

    return op-ostart;
}