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
struct TYPE_4__ {scalar_t__ const maxNbSeq; int longLengthID; size_t longLengthPos; TYPE_2__* sequencesStart; TYPE_2__* sequences; scalar_t__* mlCode; scalar_t__* ofCode; scalar_t__* llCode; } ;
typedef  TYPE_1__ seqStore_t ;
struct TYPE_5__ {scalar_t__ litLength; scalar_t__ matchLength; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ seqDef ;
typedef  scalar_t__ U32 ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ MaxLL ; 
 scalar_t__ MaxML ; 
 scalar_t__ ZSTD_LLcode (scalar_t__ const) ; 
 scalar_t__ ZSTD_MLcode (scalar_t__ const) ; 
 scalar_t__ ZSTD_highbit32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

void ZSTD_seqToCodes(const seqStore_t* seqStorePtr)
{
    const seqDef* const sequences = seqStorePtr->sequencesStart;
    BYTE* const llCodeTable = seqStorePtr->llCode;
    BYTE* const ofCodeTable = seqStorePtr->ofCode;
    BYTE* const mlCodeTable = seqStorePtr->mlCode;
    U32 const nbSeq = (U32)(seqStorePtr->sequences - seqStorePtr->sequencesStart);
    U32 u;
    assert(nbSeq <= seqStorePtr->maxNbSeq);
    for (u=0; u<nbSeq; u++) {
        U32 const llv = sequences[u].litLength;
        U32 const mlv = sequences[u].matchLength;
        llCodeTable[u] = (BYTE)ZSTD_LLcode(llv);
        ofCodeTable[u] = (BYTE)ZSTD_highbit32(sequences[u].offset);
        mlCodeTable[u] = (BYTE)ZSTD_MLcode(mlv);
    }
    if (seqStorePtr->longLengthID==1)
        llCodeTable[seqStorePtr->longLengthPos] = MaxLL;
    if (seqStorePtr->longLengthID==2)
        mlCodeTable[seqStorePtr->longLengthPos] = MaxML;
}