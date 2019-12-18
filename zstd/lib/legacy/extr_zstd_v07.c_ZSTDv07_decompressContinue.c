#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int blockType; } ;
typedef  TYPE_2__ blockProperties_t ;
struct TYPE_9__ {int /*<<< orphan*/  checksumFlag; } ;
struct TYPE_11__ {size_t expected; int stage; size_t headerBuffer; size_t headerSize; int bType; char* previousDstEnd; int /*<<< orphan*/  xxhState; TYPE_1__ fParams; } ;
typedef  TYPE_3__ ZSTDv07_DCtx ;
typedef  int U64 ;
typedef  int U32 ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int MEM_readLE32 (void const*) ; 
 int XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,void*,size_t) ; 
#define  ZSTDds_decodeBlockHeader 137 
#define  ZSTDds_decodeFrameHeader 136 
#define  ZSTDds_decodeSkippableHeader 135 
#define  ZSTDds_decompressBlock 134 
#define  ZSTDds_getFrameHeaderSize 133 
#define  ZSTDds_skipFrame 132 
 int ZSTDv07_MAGIC_SKIPPABLE_START ; 
 void* ZSTDv07_blockHeaderSize ; 
 int /*<<< orphan*/  ZSTDv07_checkContinuity (TYPE_3__*,void*) ; 
 size_t ZSTDv07_copyRawBlock (void*,size_t,void const*,size_t) ; 
 size_t ZSTDv07_decodeFrameHeader (TYPE_3__*,size_t,size_t) ; 
 size_t ZSTDv07_decompressBlock_internal (TYPE_3__*,void*,size_t,void const*,size_t) ; 
 size_t ZSTDv07_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTDv07_frameHeaderSize_min ; 
 size_t ZSTDv07_getcBlockSize (void const*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTDv07_isError (size_t const) ; 
 size_t ZSTDv07_skippableHeaderSize ; 
#define  bt_compressed 131 
#define  bt_end 130 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  checksum_wrong ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTDv07_decompressContinue(ZSTDv07_DCtx* dctx, void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
    /* Sanity check */
    if (srcSize != dctx->expected) return ERROR(srcSize_wrong);
    if (dstCapacity) ZSTDv07_checkContinuity(dctx, dst);

    switch (dctx->stage)
    {
    case ZSTDds_getFrameHeaderSize :
        if (srcSize != ZSTDv07_frameHeaderSize_min) return ERROR(srcSize_wrong);   /* impossible */
        if ((MEM_readLE32(src) & 0xFFFFFFF0U) == ZSTDv07_MAGIC_SKIPPABLE_START) {
            memcpy(dctx->headerBuffer, src, ZSTDv07_frameHeaderSize_min);
            dctx->expected = ZSTDv07_skippableHeaderSize - ZSTDv07_frameHeaderSize_min; /* magic number + skippable frame length */
            dctx->stage = ZSTDds_decodeSkippableHeader;
            return 0;
        }
        dctx->headerSize = ZSTDv07_frameHeaderSize(src, ZSTDv07_frameHeaderSize_min);
        if (ZSTDv07_isError(dctx->headerSize)) return dctx->headerSize;
        memcpy(dctx->headerBuffer, src, ZSTDv07_frameHeaderSize_min);
        if (dctx->headerSize > ZSTDv07_frameHeaderSize_min) {
            dctx->expected = dctx->headerSize - ZSTDv07_frameHeaderSize_min;
            dctx->stage = ZSTDds_decodeFrameHeader;
            return 0;
        }
        dctx->expected = 0;   /* not necessary to copy more */
	/* fall-through */
    case ZSTDds_decodeFrameHeader:
        {   size_t result;
            memcpy(dctx->headerBuffer + ZSTDv07_frameHeaderSize_min, src, dctx->expected);
            result = ZSTDv07_decodeFrameHeader(dctx, dctx->headerBuffer, dctx->headerSize);
            if (ZSTDv07_isError(result)) return result;
            dctx->expected = ZSTDv07_blockHeaderSize;
            dctx->stage = ZSTDds_decodeBlockHeader;
            return 0;
        }
    case ZSTDds_decodeBlockHeader:
        {   blockProperties_t bp;
            size_t const cBlockSize = ZSTDv07_getcBlockSize(src, ZSTDv07_blockHeaderSize, &bp);
            if (ZSTDv07_isError(cBlockSize)) return cBlockSize;
            if (bp.blockType == bt_end) {
                if (dctx->fParams.checksumFlag) {
                    U64 const h64 = XXH64_digest(&dctx->xxhState);
                    U32 const h32 = (U32)(h64>>11) & ((1<<22)-1);
                    const BYTE* const ip = (const BYTE*)src;
                    U32 const check32 = ip[2] + (ip[1] << 8) + ((ip[0] & 0x3F) << 16);
                    if (check32 != h32) return ERROR(checksum_wrong);
                }
                dctx->expected = 0;
                dctx->stage = ZSTDds_getFrameHeaderSize;
            } else {
                dctx->expected = cBlockSize;
                dctx->bType = bp.blockType;
                dctx->stage = ZSTDds_decompressBlock;
            }
            return 0;
        }
    case ZSTDds_decompressBlock:
        {   size_t rSize;
            switch(dctx->bType)
            {
            case bt_compressed:
                rSize = ZSTDv07_decompressBlock_internal(dctx, dst, dstCapacity, src, srcSize);
                break;
            case bt_raw :
                rSize = ZSTDv07_copyRawBlock(dst, dstCapacity, src, srcSize);
                break;
            case bt_rle :
                return ERROR(GENERIC);   /* not yet handled */
                break;
            case bt_end :   /* should never happen (filtered at phase 1) */
                rSize = 0;
                break;
            default:
                return ERROR(GENERIC);   /* impossible */
            }
            dctx->stage = ZSTDds_decodeBlockHeader;
            dctx->expected = ZSTDv07_blockHeaderSize;
            dctx->previousDstEnd = (char*)dst + rSize;
            if (ZSTDv07_isError(rSize)) return rSize;
            if (dctx->fParams.checksumFlag) XXH64_update(&dctx->xxhState, dst, rSize);
            return rSize;
        }
    case ZSTDds_decodeSkippableHeader:
        {   memcpy(dctx->headerBuffer + ZSTDv07_frameHeaderSize_min, src, dctx->expected);
            dctx->expected = MEM_readLE32(dctx->headerBuffer + 4);
            dctx->stage = ZSTDds_skipFrame;
            return 0;
        }
    case ZSTDds_skipFrame:
        {   dctx->expected = 0;
            dctx->stage = ZSTDds_getFrameHeaderSize;
            return 0;
        }
    default:
        return ERROR(GENERIC);   /* impossible */
    }
}