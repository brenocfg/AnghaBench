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
typedef  int /*<<< orphan*/  sequence ;
struct TYPE_9__ {int offset; } ;
typedef  TYPE_1__ seq_t ;
struct TYPE_10__ {int prevOffset; int /*<<< orphan*/  DStream; int /*<<< orphan*/  stateML; int /*<<< orphan*/  stateOffb; int /*<<< orphan*/  stateLL; int /*<<< orphan*/  const* dumpsEnd; int /*<<< orphan*/  const* dumps; } ;
typedef  TYPE_2__ seqState_t ;
struct TYPE_11__ {int litSize; scalar_t__ dictEnd; scalar_t__ vBase; scalar_t__ base; int /*<<< orphan*/ * OffTable; int /*<<< orphan*/ * MLTable; int /*<<< orphan*/ * LLTable; int /*<<< orphan*/  const* litPtr; } ;
typedef  TYPE_3__ ZSTD_DCtx ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 scalar_t__ BIT_DStream_completed ; 
 int /*<<< orphan*/  BIT_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BIT_initDStream (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BIT_reloadDStream (int /*<<< orphan*/ *) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_isError (size_t) ; 
 int /*<<< orphan*/  FSE_initDState (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t ZSTD_decodeSeqHeaders (int*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ZSTD_decodeSequence (TYPE_1__*,TYPE_2__*) ; 
 size_t ZSTD_execSequence (int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const,TYPE_1__,int /*<<< orphan*/  const**,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t ZSTD_decompressSequences(
                               ZSTD_DCtx* dctx,
                               void* dst, size_t maxDstSize,
                         const void* seqStart, size_t seqSize)
{
    const BYTE* ip = (const BYTE*)seqStart;
    const BYTE* const iend = ip + seqSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + maxDstSize;
    size_t errorCode, dumpsLength;
    const BYTE* litPtr = dctx->litPtr;
    const BYTE* const litEnd = litPtr + dctx->litSize;
    int nbSeq;
    const BYTE* dumps;
    U32* DTableLL = dctx->LLTable;
    U32* DTableML = dctx->MLTable;
    U32* DTableOffb = dctx->OffTable;
    const BYTE* const base = (const BYTE*) (dctx->base);
    const BYTE* const vBase = (const BYTE*) (dctx->vBase);
    const BYTE* const dictEnd = (const BYTE*) (dctx->dictEnd);

    /* Build Decoding Tables */
    errorCode = ZSTD_decodeSeqHeaders(&nbSeq, &dumps, &dumpsLength,
                                      DTableLL, DTableML, DTableOffb,
                                      ip, iend-ip);
    if (ZSTD_isError(errorCode)) return errorCode;
    ip += errorCode;

    /* Regen sequences */
    {
        seq_t sequence;
        seqState_t seqState;

        memset(&sequence, 0, sizeof(sequence));
        sequence.offset = 4;
        seqState.dumps = dumps;
        seqState.dumpsEnd = dumps + dumpsLength;
        seqState.prevOffset = 4;
        errorCode = BIT_initDStream(&(seqState.DStream), ip, iend-ip);
        if (ERR_isError(errorCode)) return ERROR(corruption_detected);
        FSE_initDState(&(seqState.stateLL), &(seqState.DStream), DTableLL);
        FSE_initDState(&(seqState.stateOffb), &(seqState.DStream), DTableOffb);
        FSE_initDState(&(seqState.stateML), &(seqState.DStream), DTableML);

        for ( ; (BIT_reloadDStream(&(seqState.DStream)) <= BIT_DStream_completed) && nbSeq ; )
        {
            size_t oneSeqSize;
            nbSeq--;
            ZSTD_decodeSequence(&sequence, &seqState);
            oneSeqSize = ZSTD_execSequence(op, oend, sequence, &litPtr, litEnd, base, vBase, dictEnd);
            if (ZSTD_isError(oneSeqSize)) return oneSeqSize;
            op += oneSeqSize;
        }

        /* check if reached exact end */
        if ( !BIT_endOfDStream(&(seqState.DStream)) ) return ERROR(corruption_detected);   /* DStream should be entirely and exactly consumed; otherwise data is corrupted */

        /* last literal segment */
        {
            size_t lastLLSize = litEnd - litPtr;
            if (litPtr > litEnd) return ERROR(corruption_detected);
            if (op+lastLLSize > oend) return ERROR(dstSize_tooSmall);
            if (op != litPtr) memcpy(op, litPtr, lastLLSize);
            op += lastLLSize;
        }
    }

    return op-ostart;
}