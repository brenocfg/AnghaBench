#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* bucketOffsets; } ;
typedef  TYPE_1__ ldmState_t ;
struct TYPE_8__ {int bucketSizeLog; } ;
typedef  TYPE_2__ ldmParams_t ;
typedef  int /*<<< orphan*/  ldmEntry_t ;
typedef  int U32 ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_ldm_getBucket (TYPE_1__*,size_t const,TYPE_2__ const) ; 

__attribute__((used)) static void ZSTD_ldm_insertEntry(ldmState_t* ldmState,
                                 size_t const hash, const ldmEntry_t entry,
                                 ldmParams_t const ldmParams)
{
    BYTE* const bucketOffsets = ldmState->bucketOffsets;
    *(ZSTD_ldm_getBucket(ldmState, hash, ldmParams) + bucketOffsets[hash]) = entry;
    bucketOffsets[hash]++;
    bucketOffsets[hash] &= ((U32)1 << ldmParams.bucketSizeLog) - 1;
}