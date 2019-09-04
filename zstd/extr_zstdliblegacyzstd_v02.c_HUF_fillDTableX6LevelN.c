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
struct TYPE_9__ {int weight; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ sortedSymbol_t ;
typedef  int /*<<< orphan*/ * rankVal_t ;
typedef  int /*<<< orphan*/  rankVal ;
typedef  int U32 ;
struct TYPE_11__ {int nbBytes; int /*<<< orphan*/  nbBits; } ;
struct TYPE_10__ {int /*<<< orphan*/ * byte; } ;
typedef  TYPE_2__ HUF_DSeqX6 ;
typedef  TYPE_3__ HUF_DDescX6 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HUF_ABSOLUTEMAX_TABLELOG ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void HUF_fillDTableX6LevelN(HUF_DDescX6* DDescription, HUF_DSeqX6* DSequence, int sizeLog,
                           const rankVal_t rankValOrigin, const U32 consumed, const int minWeight, const U32 maxWeight,
                           const sortedSymbol_t* sortedSymbols, const U32 sortedListSize, const U32* rankStart,
                           const U32 nbBitsBaseline, HUF_DSeqX6 baseSeq, HUF_DDescX6 DDesc)
{
    const int scaleLog = nbBitsBaseline - sizeLog;   /* note : targetLog >= (nbBitsBaseline-1), hence scaleLog <= 1 */
    const int minBits  = nbBitsBaseline - maxWeight;
    const U32 level = DDesc.nbBytes;
    U32 rankVal[HUF_ABSOLUTEMAX_TABLELOG + 1];
    U32 symbolStartPos, s;

    /* local rankVal, will be modified */
    memcpy(rankVal, rankValOrigin[consumed], sizeof(rankVal));

    /* fill skipped values */
    if (minWeight>1)
    {
        U32 i;
        const U32 skipSize = rankVal[minWeight];
        for (i = 0; i < skipSize; i++)
        {
            DSequence[i] = baseSeq;
            DDescription[i] = DDesc;
        }
    }

    /* fill DTable */
    DDesc.nbBytes++;
    symbolStartPos = rankStart[minWeight];
    for (s=symbolStartPos; s<sortedListSize; s++)
    {
        const BYTE symbol = sortedSymbols[s].symbol;
        const U32  weight = sortedSymbols[s].weight;   /* >= 1 (sorted) */
        const int  nbBits = nbBitsBaseline - weight;   /* >= 1 (by construction) */
        const int  totalBits = consumed+nbBits;
        const U32  start  = rankVal[weight];
        const U32  length = 1 << (sizeLog-nbBits);
        baseSeq.byte[level] = symbol;
        DDesc.nbBits = (BYTE)totalBits;

        if ((level<3) && (sizeLog-totalBits >= minBits))   /* enough room for another symbol */
        {
            int nextMinWeight = totalBits + scaleLog;
            if (nextMinWeight < 1) nextMinWeight = 1;
            HUF_fillDTableX6LevelN(DDescription+start, DSequence+start, sizeLog-nbBits,
                           rankValOrigin, totalBits, nextMinWeight, maxWeight,
                           sortedSymbols, sortedListSize, rankStart,
                           nbBitsBaseline, baseSeq, DDesc);   /* recursive (max : level 3) */
        }
        else
        {
            U32 i;
            const U32 end = start + length;
            for (i = start; i < end; i++)
            {
                DDescription[i] = DDesc;
                DSequence[i] = baseSeq;
            }
        }
        rankVal[weight] += length;
    }
}