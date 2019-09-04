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
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;
struct TYPE_7__ {int hashLog; int searchLength; int chainLog; } ;
struct TYPE_6__ {int* hashTable; int* chainTable; int nextToUpdate; TYPE_1__ window; TYPE_3__ cParams; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  scalar_t__ ZSTD_dictTableLoadMethod_e ;
typedef  TYPE_3__ ZSTD_compressionParameters ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  const* HASH_READ_SIZE ; 
 scalar_t__ ZSTD_dtlm_fast ; 
 size_t ZSTD_hashPtr (int /*<<< orphan*/  const*,int const,int const) ; 

void ZSTD_fillDoubleHashTable(ZSTD_matchState_t* ms,
                              void const* end, ZSTD_dictTableLoadMethod_e dtlm)
{
    const ZSTD_compressionParameters* const cParams = &ms->cParams;
    U32* const hashLarge = ms->hashTable;
    U32  const hBitsL = cParams->hashLog;
    U32  const mls = cParams->searchLength;
    U32* const hashSmall = ms->chainTable;
    U32  const hBitsS = cParams->chainLog;
    const BYTE* const base = ms->window.base;
    const BYTE* ip = base + ms->nextToUpdate;
    const BYTE* const iend = ((const BYTE*)end) - HASH_READ_SIZE;
    const U32 fastHashFillStep = 3;

    /* Always insert every fastHashFillStep position into the hash tables.
     * Insert the other positions into the large hash table if their entry
     * is empty.
     */
    for (; ip + fastHashFillStep - 1 <= iend; ip += fastHashFillStep) {
        U32 const current = (U32)(ip - base);
        U32 i;
        for (i = 0; i < fastHashFillStep; ++i) {
            size_t const smHash = ZSTD_hashPtr(ip + i, hBitsS, mls);
            size_t const lgHash = ZSTD_hashPtr(ip + i, hBitsL, 8);
            if (i == 0)
                hashSmall[smHash] = current + i;
            if (i == 0 || hashLarge[lgHash] == 0)
                hashLarge[lgHash] = current + i;
            /* Only load extra positions for ZSTD_dtlm_full */
            if (dtlm == ZSTD_dtlm_fast)
                break;
        }
    }
}