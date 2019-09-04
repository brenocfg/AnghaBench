#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldmState_t ;
struct TYPE_6__ {int hashEveryLog; } ;
typedef  TYPE_1__ ldmParams_t ;
struct TYPE_7__ {int offset; int checksum; } ;
typedef  TYPE_2__ ldmEntry_t ;
typedef  int /*<<< orphan*/  U64 ;
typedef  int U32 ;

/* Variables and functions */
 int ZSTD_ldm_getChecksum (int /*<<< orphan*/  const,int const) ; 
 int ZSTD_ldm_getSmallHash (int /*<<< orphan*/  const,int const) ; 
 int ZSTD_ldm_getTag (int /*<<< orphan*/  const,int const,int) ; 
 int /*<<< orphan*/  ZSTD_ldm_insertEntry (int /*<<< orphan*/ *,int const,TYPE_2__,TYPE_1__ const) ; 

__attribute__((used)) static void ZSTD_ldm_makeEntryAndInsertByTag(ldmState_t* ldmState,
                                             U64 const rollingHash,
                                             U32 const hBits,
                                             U32 const offset,
                                             ldmParams_t const ldmParams)
{
    U32 const tag = ZSTD_ldm_getTag(rollingHash, hBits, ldmParams.hashEveryLog);
    U32 const tagMask = ((U32)1 << ldmParams.hashEveryLog) - 1;
    if (tag == tagMask) {
        U32 const hash = ZSTD_ldm_getSmallHash(rollingHash, hBits);
        U32 const checksum = ZSTD_ldm_getChecksum(rollingHash, hBits);
        ldmEntry_t entry;
        entry.offset = offset;
        entry.checksum = checksum;
        ZSTD_ldm_insertEntry(ldmState, hash, entry, ldmParams);
    }
}