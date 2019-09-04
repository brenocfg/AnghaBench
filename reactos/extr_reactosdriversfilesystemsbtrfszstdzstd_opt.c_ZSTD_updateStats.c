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
struct TYPE_3__ {size_t* litFreq; size_t litSum; int /*<<< orphan*/  matchLengthSum; int /*<<< orphan*/ * matchLengthFreq; int /*<<< orphan*/  offCodeSum; int /*<<< orphan*/ * offCodeFreq; int /*<<< orphan*/  litLengthSum; int /*<<< orphan*/ * litLengthFreq; } ;
typedef  TYPE_1__ optState_t ;
typedef  size_t U32 ;
typedef  size_t BYTE ;

/* Variables and functions */
 size_t MINMATCH ; 
 size_t const MaxOff ; 
 size_t ZSTD_LITFREQ_ADD ; 
 size_t ZSTD_LLcode (size_t) ; 
 size_t ZSTD_MLcode (size_t const) ; 
 size_t ZSTD_highbit32 (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void ZSTD_updateStats(optState_t* const optPtr,
                             U32 litLength, const BYTE* literals,
                             U32 offsetCode, U32 matchLength)
{
    /* literals */
    {   U32 u;
        for (u=0; u < litLength; u++)
            optPtr->litFreq[literals[u]] += ZSTD_LITFREQ_ADD;
        optPtr->litSum += litLength*ZSTD_LITFREQ_ADD;
    }

    /* literal Length */
    {   U32 const llCode = ZSTD_LLcode(litLength);
        optPtr->litLengthFreq[llCode]++;
        optPtr->litLengthSum++;
    }

    /* match offset code (0-2=>repCode; 3+=>offset+2) */
    {   U32 const offCode = ZSTD_highbit32(offsetCode+1);
        assert(offCode <= MaxOff);
        optPtr->offCodeFreq[offCode]++;
        optPtr->offCodeSum++;
    }

    /* match Length */
    {   U32 const mlBase = matchLength - MINMATCH;
        U32 const mlCode = ZSTD_MLcode(mlBase);
        optPtr->matchLengthFreq[mlCode]++;
        optPtr->matchLengthSum++;
    }
}