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
struct TYPE_10__ {int /*<<< orphan*/  lastBlock; int /*<<< orphan*/  origSize; int /*<<< orphan*/  blockType; } ;
typedef  TYPE_2__ blockProperties_t ;
struct TYPE_9__ {int /*<<< orphan*/  checksumFlag; } ;
struct TYPE_11__ {size_t expected; int stage; size_t headerBuffer; size_t headerSize; char* previousDstEnd; int /*<<< orphan*/  xxhState; TYPE_1__ fParams; int /*<<< orphan*/  rleSize; int /*<<< orphan*/  bType; } ;
typedef  TYPE_3__ ZSTD_DCtx ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int ZSTD_MAGIC_SKIPPABLE_START ; 
 void* ZSTD_blockHeaderSize ; 
 int /*<<< orphan*/  ZSTD_checkContinuity (TYPE_3__*,void*) ; 
 size_t ZSTD_copyRawBlock (void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_decodeFrameHeader (TYPE_3__*,size_t,size_t) ; 
 size_t ZSTD_decompressBlock_internal (TYPE_3__*,void*,size_t,void const*,size_t) ; 
 size_t ZSTD_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTD_frameHeaderSize_prefix ; 
 size_t ZSTD_getcBlockSize (void const*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t const) ; 
 int ZSTD_readLE32 (void const*) ; 
 size_t ZSTD_setRleBlock (void*,size_t,void const*,size_t,int /*<<< orphan*/ ) ; 
 size_t ZSTD_skippableHeaderSize ; 
#define  ZSTDds_checkChecksum 139 
#define  ZSTDds_decodeBlockHeader 138 
#define  ZSTDds_decodeFrameHeader 137 
#define  ZSTDds_decodeSkippableHeader 136 
#define  ZSTDds_decompressBlock 135 
#define  ZSTDds_decompressLastBlock 134 
#define  ZSTDds_getFrameHeaderSize 133 
#define  ZSTDds_skipFrame 132 
#define  bt_compressed 131 
#define  bt_raw 130 
#define  bt_reserved 129 
#define  bt_rle 128 
 int /*<<< orphan*/  checksum_wrong ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 
 int /*<<< orphan*/  xxh64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xxh64_update (int /*<<< orphan*/ *,void*,size_t) ; 

size_t ZSTD_decompressContinue(ZSTD_DCtx *dctx, void *dst, size_t dstCapacity, const void *src, size_t srcSize)
{
	/* Sanity check */
	if (srcSize != dctx->expected)
		return ERROR(srcSize_wrong);
	if (dstCapacity)
		ZSTD_checkContinuity(dctx, dst);

	switch (dctx->stage) {
	case ZSTDds_getFrameHeaderSize:
		if (srcSize != ZSTD_frameHeaderSize_prefix)
			return ERROR(srcSize_wrong);					/* impossible */
		if ((ZSTD_readLE32(src) & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) { /* skippable frame */
			memcpy(dctx->headerBuffer, src, ZSTD_frameHeaderSize_prefix);
			dctx->expected = ZSTD_skippableHeaderSize - ZSTD_frameHeaderSize_prefix; /* magic number + skippable frame length */
			dctx->stage = ZSTDds_decodeSkippableHeader;
			return 0;
		}
		dctx->headerSize = ZSTD_frameHeaderSize(src, ZSTD_frameHeaderSize_prefix);
		if (ZSTD_isError(dctx->headerSize))
			return dctx->headerSize;
		memcpy(dctx->headerBuffer, src, ZSTD_frameHeaderSize_prefix);
		if (dctx->headerSize > ZSTD_frameHeaderSize_prefix) {
			dctx->expected = dctx->headerSize - ZSTD_frameHeaderSize_prefix;
			dctx->stage = ZSTDds_decodeFrameHeader;
			return 0;
		}
		dctx->expected = 0; /* not necessary to copy more */

	case ZSTDds_decodeFrameHeader:
		memcpy(dctx->headerBuffer + ZSTD_frameHeaderSize_prefix, src, dctx->expected);
		CHECK_F(ZSTD_decodeFrameHeader(dctx, dctx->headerBuffer, dctx->headerSize));
		dctx->expected = ZSTD_blockHeaderSize;
		dctx->stage = ZSTDds_decodeBlockHeader;
		return 0;

	case ZSTDds_decodeBlockHeader: {
		blockProperties_t bp;
		size_t const cBlockSize = ZSTD_getcBlockSize(src, ZSTD_blockHeaderSize, &bp);
		if (ZSTD_isError(cBlockSize))
			return cBlockSize;
		dctx->expected = cBlockSize;
		dctx->bType = bp.blockType;
		dctx->rleSize = bp.origSize;
		if (cBlockSize) {
			dctx->stage = bp.lastBlock ? ZSTDds_decompressLastBlock : ZSTDds_decompressBlock;
			return 0;
		}
		/* empty block */
		if (bp.lastBlock) {
			if (dctx->fParams.checksumFlag) {
				dctx->expected = 4;
				dctx->stage = ZSTDds_checkChecksum;
			} else {
				dctx->expected = 0; /* end of frame */
				dctx->stage = ZSTDds_getFrameHeaderSize;
			}
		} else {
			dctx->expected = 3; /* go directly to next header */
			dctx->stage = ZSTDds_decodeBlockHeader;
		}
		return 0;
	}
	case ZSTDds_decompressLastBlock:
	case ZSTDds_decompressBlock: {
		size_t rSize;
		switch (dctx->bType) {
		case bt_compressed: rSize = ZSTD_decompressBlock_internal(dctx, dst, dstCapacity, src, srcSize); break;
		case bt_raw: rSize = ZSTD_copyRawBlock(dst, dstCapacity, src, srcSize); break;
		case bt_rle: rSize = ZSTD_setRleBlock(dst, dstCapacity, src, srcSize, dctx->rleSize); break;
		case bt_reserved: /* should never happen */
		default: return ERROR(corruption_detected);
		}
		if (ZSTD_isError(rSize))
			return rSize;
		if (dctx->fParams.checksumFlag)
			xxh64_update(&dctx->xxhState, dst, rSize);

		if (dctx->stage == ZSTDds_decompressLastBlock) { /* end of frame */
			if (dctx->fParams.checksumFlag) {	/* another round for frame checksum */
				dctx->expected = 4;
				dctx->stage = ZSTDds_checkChecksum;
			} else {
				dctx->expected = 0; /* ends here */
				dctx->stage = ZSTDds_getFrameHeaderSize;
			}
		} else {
			dctx->stage = ZSTDds_decodeBlockHeader;
			dctx->expected = ZSTD_blockHeaderSize;
			dctx->previousDstEnd = (char *)dst + rSize;
		}
		return rSize;
	}
	case ZSTDds_checkChecksum: {
		U32 const h32 = (U32)xxh64_digest(&dctx->xxhState);
		U32 const check32 = ZSTD_readLE32(src); /* srcSize == 4, guaranteed by dctx->expected */
		if (check32 != h32)
			return ERROR(checksum_wrong);
		dctx->expected = 0;
		dctx->stage = ZSTDds_getFrameHeaderSize;
		return 0;
	}
	case ZSTDds_decodeSkippableHeader: {
		memcpy(dctx->headerBuffer + ZSTD_frameHeaderSize_prefix, src, dctx->expected);
		dctx->expected = ZSTD_readLE32(dctx->headerBuffer + 4);
		dctx->stage = ZSTDds_skipFrame;
		return 0;
	}
	case ZSTDds_skipFrame: {
		dctx->expected = 0;
		dctx->stage = ZSTDds_getFrameHeaderSize;
		return 0;
	}
	default:
		return ERROR(GENERIC); /* impossible */
	}
}