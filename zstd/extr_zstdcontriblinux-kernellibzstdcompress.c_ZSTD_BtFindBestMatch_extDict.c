#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nextToUpdate; int /*<<< orphan*/  const* const base; } ;
typedef  TYPE_1__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ZSTD_insertBtAndFindBestMatch (TYPE_1__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,size_t*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ZSTD_updateTree_extDict (TYPE_1__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static size_t ZSTD_BtFindBestMatch_extDict(ZSTD_CCtx *zc, const BYTE *const ip, const BYTE *const iLimit, size_t *offsetPtr, const U32 maxNbAttempts,
					   const U32 mls)
{
	if (ip < zc->base + zc->nextToUpdate)
		return 0; /* skipped area */
	ZSTD_updateTree_extDict(zc, ip, iLimit, maxNbAttempts, mls);
	return ZSTD_insertBtAndFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, mls, 1);
}