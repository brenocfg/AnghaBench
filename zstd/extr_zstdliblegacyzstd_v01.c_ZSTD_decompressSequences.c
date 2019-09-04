#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sequence ;
typedef  int /*<<< orphan*/  seq_t ;
struct TYPE_4__ {int prevOffset; int /*<<< orphan*/  DStream; int /*<<< orphan*/  stateML; int /*<<< orphan*/  stateOffb; int /*<<< orphan*/  stateLL; int /*<<< orphan*/  const* dumpsEnd; int /*<<< orphan*/  const* dumps; } ;
typedef  TYPE_1__ seqState_t ;
struct TYPE_5__ {scalar_t__ base; int /*<<< orphan*/ * OffTable; int /*<<< orphan*/ * MLTable; int /*<<< orphan*/ * LLTable; } ;
typedef  TYPE_2__ dctx_t ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ FSE_DStream_completed ; 
 int /*<<< orphan*/  FSE_endOfDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSE_initDState (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t FSE_initDStream (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ FSE_isError (size_t) ; 
 scalar_t__ FSE_reloadDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_decodeSequence (int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t ZSTD_execSequence (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 size_t ZSTDv01_decodeSeqHeaders (int*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ZSTDv01_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t ZSTD_decompressSequences(
                               void* ctx,
                               void* dst, size_t maxDstSize,
                         const void* seqStart, size_t seqSize,
                         const BYTE* litStart, size_t litSize)
{
    dctx_t* dctx = (dctx_t*)ctx;
    const BYTE* ip = (const BYTE*)seqStart;
    const BYTE* const iend = ip + seqSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + maxDstSize;
    size_t errorCode, dumpsLength;
    const BYTE* litPtr = litStart;
    const BYTE* const litEnd = litStart + litSize;
    int nbSeq;
    const BYTE* dumps;
    U32* DTableLL = dctx->LLTable;
    U32* DTableML = dctx->MLTable;
    U32* DTableOffb = dctx->OffTable;
    BYTE* const base = (BYTE*) (dctx->base);

    /* Build Decoding Tables */
    errorCode = ZSTDv01_decodeSeqHeaders(&nbSeq, &dumps, &dumpsLength,
                                      DTableLL, DTableML, DTableOffb,
                                      ip, iend-ip);
    if (ZSTDv01_isError(errorCode)) return errorCode;
    ip += errorCode;

    /* Regen sequences */
    {
        seq_t sequence;
        seqState_t seqState;

        memset(&sequence, 0, sizeof(sequence));
        seqState.dumps = dumps;
        seqState.dumpsEnd = dumps + dumpsLength;
        seqState.prevOffset = 1;
        errorCode = FSE_initDStream(&(seqState.DStream), ip, iend-ip);
        if (FSE_isError(errorCode)) return ERROR(corruption_detected);
        FSE_initDState(&(seqState.stateLL), &(seqState.DStream), DTableLL);
        FSE_initDState(&(seqState.stateOffb), &(seqState.DStream), DTableOffb);
        FSE_initDState(&(seqState.stateML), &(seqState.DStream), DTableML);

        for ( ; (FSE_reloadDStream(&(seqState.DStream)) <= FSE_DStream_completed) && (nbSeq>0) ; )
        {
            size_t oneSeqSize;
            nbSeq--;
            ZSTD_decodeSequence(&sequence, &seqState);
            oneSeqSize = ZSTD_execSequence(op, sequence, &litPtr, litEnd, base, oend);
            if (ZSTDv01_isError(oneSeqSize)) return oneSeqSize;
            op += oneSeqSize;
        }

        /* check if reached exact end */
        if ( !FSE_endOfDStream(&(seqState.DStream)) ) return ERROR(corruption_detected);   /* requested too much : data is corrupted */
        if (nbSeq<0) return ERROR(corruption_detected);   /* requested too many sequences : data is corrupted */

        /* last literal segment */
        {
            size_t lastLLSize = litEnd - litPtr;
            if (op+lastLLSize > oend) return ERROR(dstSize_tooSmall);
            if (op != litPtr) memmove(op, litPtr, lastLLSize);
            op += lastLLSize;
        }
    }

    return op-ostart;
}