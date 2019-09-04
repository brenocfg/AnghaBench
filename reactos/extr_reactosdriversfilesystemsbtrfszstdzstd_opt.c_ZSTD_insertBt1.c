#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* base; scalar_t__* dictBase; int dictLimit; int lowLimit; } ;
struct TYPE_7__ {int hashLog; int chainLog; unsigned int searchLog; } ;
struct TYPE_6__ {int* hashTable; int* chainTable; TYPE_1__ window; TYPE_3__ cParams; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  TYPE_3__ ZSTD_compressionParameters ;
typedef  int U32 ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int const) ; 
 int MIN (int,int) ; 
 scalar_t__ ZSTD_count (scalar_t__ const* const,scalar_t__ const*,scalar_t__ const* const) ; 
 scalar_t__ ZSTD_count_2segments (scalar_t__ const* const,scalar_t__ const*,scalar_t__ const* const,scalar_t__ const* const,scalar_t__ const* const) ; 
 size_t ZSTD_hashPtr (scalar_t__ const* const,int const,int const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static U32 ZSTD_insertBt1(
                ZSTD_matchState_t* ms,
                const BYTE* const ip, const BYTE* const iend,
                U32 const mls, const int extDict)
{
    const ZSTD_compressionParameters* const cParams = &ms->cParams;
    U32*   const hashTable = ms->hashTable;
    U32    const hashLog = cParams->hashLog;
    size_t const h  = ZSTD_hashPtr(ip, hashLog, mls);
    U32*   const bt = ms->chainTable;
    U32    const btLog  = cParams->chainLog - 1;
    U32    const btMask = (1 << btLog) - 1;
    U32 matchIndex = hashTable[h];
    size_t commonLengthSmaller=0, commonLengthLarger=0;
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const U32 dictLimit = ms->window.dictLimit;
    const BYTE* const dictEnd = dictBase + dictLimit;
    const BYTE* const prefixStart = base + dictLimit;
    const BYTE* match;
    const U32 current = (U32)(ip-base);
    const U32 btLow = btMask >= current ? 0 : current - btMask;
    U32* smallerPtr = bt + 2*(current&btMask);
    U32* largerPtr  = smallerPtr + 1;
    U32 dummy32;   /* to be nullified at the end */
    U32 const windowLow = ms->window.lowLimit;
    U32 const matchLow = windowLow ? windowLow : 1;
    U32 matchEndIdx = current+8+1;
    size_t bestLength = 8;
    U32 nbCompares = 1U << cParams->searchLog;
#ifdef ZSTD_C_PREDICT
    U32 predictedSmall = *(bt + 2*((current-1)&btMask) + 0);
    U32 predictedLarge = *(bt + 2*((current-1)&btMask) + 1);
    predictedSmall += (predictedSmall>0);
    predictedLarge += (predictedLarge>0);
#endif /* ZSTD_C_PREDICT */

    DEBUGLOG(8, "ZSTD_insertBt1 (%u)", current);

    assert(ip <= iend-8);   /* required for h calculation */
    hashTable[h] = current;   /* Update Hash Table */

    while (nbCompares-- && (matchIndex >= matchLow)) {
        U32* const nextPtr = bt + 2*(matchIndex & btMask);
        size_t matchLength = MIN(commonLengthSmaller, commonLengthLarger);   /* guaranteed minimum nb of common bytes */
        assert(matchIndex < current);

#ifdef ZSTD_C_PREDICT   /* note : can create issues when hlog small <= 11 */
        const U32* predictPtr = bt + 2*((matchIndex-1) & btMask);   /* written this way, as bt is a roll buffer */
        if (matchIndex == predictedSmall) {
            /* no need to check length, result known */
            *smallerPtr = matchIndex;
            if (matchIndex <= btLow) { smallerPtr=&dummy32; break; }   /* beyond tree size, stop the search */
            smallerPtr = nextPtr+1;               /* new "smaller" => larger of match */
            matchIndex = nextPtr[1];              /* new matchIndex larger than previous (closer to current) */
            predictedSmall = predictPtr[1] + (predictPtr[1]>0);
            continue;
        }
        if (matchIndex == predictedLarge) {
            *largerPtr = matchIndex;
            if (matchIndex <= btLow) { largerPtr=&dummy32; break; }   /* beyond tree size, stop the search */
            largerPtr = nextPtr;
            matchIndex = nextPtr[0];
            predictedLarge = predictPtr[0] + (predictPtr[0]>0);
            continue;
        }
#endif

        if (!extDict || (matchIndex+matchLength >= dictLimit)) {
            assert(matchIndex+matchLength >= dictLimit);   /* might be wrong if actually extDict */
            match = base + matchIndex;
            matchLength += ZSTD_count(ip+matchLength, match+matchLength, iend);
        } else {
            match = dictBase + matchIndex;
            matchLength += ZSTD_count_2segments(ip+matchLength, match+matchLength, iend, dictEnd, prefixStart);
            if (matchIndex+matchLength >= dictLimit)
                match = base + matchIndex;   /* to prepare for next usage of match[matchLength] */
        }

        if (matchLength > bestLength) {
            bestLength = matchLength;
            if (matchLength > matchEndIdx - matchIndex)
                matchEndIdx = matchIndex + (U32)matchLength;
        }

        if (ip+matchLength == iend) {   /* equal : no way to know if inf or sup */
            break;   /* drop , to guarantee consistency ; miss a bit of compression, but other solutions can corrupt tree */
        }

        if (match[matchLength] < ip[matchLength]) {  /* necessarily within buffer */
            /* match is smaller than current */
            *smallerPtr = matchIndex;             /* update smaller idx */
            commonLengthSmaller = matchLength;    /* all smaller will now have at least this guaranteed common length */
            if (matchIndex <= btLow) { smallerPtr=&dummy32; break; }   /* beyond tree size, stop searching */
            smallerPtr = nextPtr+1;               /* new "candidate" => larger than match, which was smaller than target */
            matchIndex = nextPtr[1];              /* new matchIndex, larger than previous and closer to current */
        } else {
            /* match is larger than current */
            *largerPtr = matchIndex;
            commonLengthLarger = matchLength;
            if (matchIndex <= btLow) { largerPtr=&dummy32; break; }   /* beyond tree size, stop searching */
            largerPtr = nextPtr;
            matchIndex = nextPtr[0];
    }   }

    *smallerPtr = *largerPtr = 0;
    if (bestLength > 384) return MIN(192, (U32)(bestLength - 384));   /* speed optimization */
    assert(matchEndIdx > current + 8);
    return matchEndIdx - (current + 8);
}