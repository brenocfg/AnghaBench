#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t longLengthPos; int longLengthID; TYPE_3__ const* sequences; TYPE_3__* sequencesStart; } ;
typedef  TYPE_2__ seqStore_t ;
struct TYPE_11__ {unsigned int offset; scalar_t__ litLength; scalar_t__ matchLength; } ;
typedef  TYPE_3__ seqDef ;
struct TYPE_12__ {unsigned int offset; scalar_t__ litLength; unsigned int rep; unsigned int matchPos; scalar_t__ matchLength; } ;
typedef  TYPE_4__ ZSTD_Sequence ;
struct TYPE_9__ {size_t seqIndex; int maxSequences; TYPE_4__* seqStart; } ;
struct TYPE_13__ {TYPE_1__ seqCollector; } ;
typedef  TYPE_5__ ZSTD_CCtx ;

/* Variables and functions */
 scalar_t__ MINMATCH ; 
 unsigned int ZSTD_REP_NUM ; 
 TYPE_2__* ZSTD_getSeqStore (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* repStartValue ; 

__attribute__((used)) static void ZSTD_copyBlockSequences(ZSTD_CCtx* zc)
{
    const seqStore_t* seqStore = ZSTD_getSeqStore(zc);
    const seqDef* seqs = seqStore->sequencesStart;
    size_t seqsSize = seqStore->sequences - seqs;

    ZSTD_Sequence* outSeqs = &zc->seqCollector.seqStart[zc->seqCollector.seqIndex];
    size_t i; size_t position; int repIdx;

    assert(zc->seqCollector.seqIndex + 1 < zc->seqCollector.maxSequences);
    for (i = 0, position = 0; i < seqsSize; ++i) {
        outSeqs[i].offset = seqs[i].offset;
        outSeqs[i].litLength = seqs[i].litLength;
        outSeqs[i].matchLength = seqs[i].matchLength + MINMATCH;

        if (i == seqStore->longLengthPos) {
            if (seqStore->longLengthID == 1) {
                outSeqs[i].litLength += 0x10000;
            } else if (seqStore->longLengthID == 2) {
                outSeqs[i].matchLength += 0x10000;
            }
        }

        if (outSeqs[i].offset <= ZSTD_REP_NUM) {
            outSeqs[i].rep = outSeqs[i].offset;
            repIdx = (unsigned int)i - outSeqs[i].offset;

            if (outSeqs[i].litLength == 0) {
                if (outSeqs[i].offset < 3) {
                    --repIdx;
                } else {
                    repIdx = (unsigned int)i - 1;
                }
                ++outSeqs[i].rep;
            }
            assert(repIdx >= -3);
            outSeqs[i].offset = repIdx >= 0 ? outSeqs[repIdx].offset : repStartValue[-repIdx - 1];
            if (outSeqs[i].rep == 4) {
                --outSeqs[i].offset;
            }
        } else {
            outSeqs[i].offset -= ZSTD_REP_NUM;
        }

        position += outSeqs[i].litLength;
        outSeqs[i].matchPos = (unsigned int)position;
        position += outSeqs[i].matchLength;
    }
    zc->seqCollector.seqIndex += seqsSize;
}