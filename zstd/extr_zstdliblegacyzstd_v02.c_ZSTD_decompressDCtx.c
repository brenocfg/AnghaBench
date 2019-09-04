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
struct TYPE_3__ {int blockType; } ;
typedef  TYPE_1__ blockProperties_t ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 size_t ZSTD_blockHeaderSize ; 
 size_t ZSTD_copyUncompressedBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t) ; 
 size_t ZSTD_decompressBlock (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t) ; 
 size_t ZSTD_frameHeaderSize ; 
 size_t ZSTD_getcBlockSize (int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 scalar_t__ ZSTD_magicNumber ; 
#define  bt_compressed 131 
#define  bt_end 130 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_decompressDCtx(void* ctx, void* dst, size_t maxDstSize, const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    const BYTE* iend = ip + srcSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + maxDstSize;
    size_t remainingSize = srcSize;
    U32 magicNumber;
    blockProperties_t blockProperties;

    /* Frame Header */
    if (srcSize < ZSTD_frameHeaderSize+ZSTD_blockHeaderSize) return ERROR(srcSize_wrong);
    magicNumber = MEM_readLE32(src);
    if (magicNumber != ZSTD_magicNumber) return ERROR(prefix_unknown);
    ip += ZSTD_frameHeaderSize; remainingSize -= ZSTD_frameHeaderSize;

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
            decodedSize = ZSTD_decompressBlock(ctx, op, oend-op, ip, cBlockSize);
            break;
        case bt_raw :
            decodedSize = ZSTD_copyUncompressedBlock(op, oend-op, ip, cBlockSize);
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