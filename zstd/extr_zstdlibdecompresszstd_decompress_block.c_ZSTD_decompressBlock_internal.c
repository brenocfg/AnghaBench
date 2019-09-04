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
typedef  int /*<<< orphan*/  ZSTD_longOffset_e ;
struct TYPE_8__ {unsigned long long windowSize; } ;
struct TYPE_9__ {int ddictIsCold; int /*<<< orphan*/  OFTptr; TYPE_1__ fParams; } ;
typedef  TYPE_2__ ZSTD_DCtx ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ADVANCED_SEQS ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,scalar_t__) ; 
 scalar_t__ MEM_32bits () ; 
 scalar_t__ MEM_64bits () ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 unsigned long long STREAM_ACCUMULATOR_MIN ; 
 size_t ZSTD_BLOCKSIZE_MAX ; 
 size_t ZSTD_decodeLiteralsBlock (TYPE_2__*,void const*,size_t) ; 
 size_t ZSTD_decodeSeqHeaders (TYPE_2__*,int*,int /*<<< orphan*/  const*,size_t) ; 
 size_t ZSTD_decompressSequences (TYPE_2__*,void*,size_t,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const) ; 
 size_t ZSTD_decompressSequencesLong (TYPE_2__*,void*,size_t,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const) ; 
 scalar_t__ ZSTD_getLongOffsetsShare (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t
ZSTD_decompressBlock_internal(ZSTD_DCtx* dctx,
                              void* dst, size_t dstCapacity,
                        const void* src, size_t srcSize, const int frame)
{   /* blockType == blockCompressed */
    const BYTE* ip = (const BYTE*)src;
    /* isLongOffset must be true if there are long offsets.
     * Offsets are long if they are larger than 2^STREAM_ACCUMULATOR_MIN.
     * We don't expect that to be the case in 64-bit mode.
     * In block mode, window size is not known, so we have to be conservative.
     * (note: but it could be evaluated from current-lowLimit)
     */
    ZSTD_longOffset_e const isLongOffset = (ZSTD_longOffset_e)(MEM_32bits() && (!frame || (dctx->fParams.windowSize > (1ULL << STREAM_ACCUMULATOR_MIN))));
    DEBUGLOG(5, "ZSTD_decompressBlock_internal (size : %u)", (U32)srcSize);

    RETURN_ERROR_IF(srcSize >= ZSTD_BLOCKSIZE_MAX, srcSize_wrong);

    /* Decode literals section */
    {   size_t const litCSize = ZSTD_decodeLiteralsBlock(dctx, src, srcSize);
        DEBUGLOG(5, "ZSTD_decodeLiteralsBlock : %u", (U32)litCSize);
        if (ZSTD_isError(litCSize)) return litCSize;
        ip += litCSize;
        srcSize -= litCSize;
    }

    /* Build Decoding Tables */
    {
        /* These macros control at build-time which decompressor implementation
         * we use. If neither is defined, we do some inspection and dispatch at
         * runtime.
         */
#if !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT) && \
    !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG)
        int usePrefetchDecoder = dctx->ddictIsCold;
#endif
        int nbSeq;
        size_t const seqHSize = ZSTD_decodeSeqHeaders(dctx, &nbSeq, ip, srcSize);
        if (ZSTD_isError(seqHSize)) return seqHSize;
        ip += seqHSize;
        srcSize -= seqHSize;

#if !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT) && \
    !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG)
        if ( !usePrefetchDecoder
          && (!frame || (dctx->fParams.windowSize > (1<<24)))
          && (nbSeq>ADVANCED_SEQS) ) {  /* could probably use a larger nbSeq limit */
            U32 const shareLongOffsets = ZSTD_getLongOffsetsShare(dctx->OFTptr);
            U32 const minShare = MEM_64bits() ? 7 : 20; /* heuristic values, correspond to 2.73% and 7.81% */
            usePrefetchDecoder = (shareLongOffsets >= minShare);
        }
#endif

        dctx->ddictIsCold = 0;

#if !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT) && \
    !defined(ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG)
        if (usePrefetchDecoder)
#endif
#ifndef ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT
            return ZSTD_decompressSequencesLong(dctx, dst, dstCapacity, ip, srcSize, nbSeq, isLongOffset);
#endif

#ifndef ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG
        /* else */
        return ZSTD_decompressSequences(dctx, dst, dstCapacity, ip, srcSize, nbSeq, isLongOffset);
#endif
    }
}