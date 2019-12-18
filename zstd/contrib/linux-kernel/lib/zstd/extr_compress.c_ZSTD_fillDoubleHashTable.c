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
struct TYPE_5__ {int hashLog; int chainLog; } ;
struct TYPE_6__ {TYPE_1__ cParams; } ;
struct TYPE_7__ {int* hashTable; int* chainTable; int nextToUpdate; int /*<<< orphan*/ * base; TYPE_2__ params; } ;
typedef  TYPE_3__ ZSTD_CCtx ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  const* HASH_READ_SIZE ; 
 size_t ZSTD_hashPtr (int /*<<< orphan*/  const*,int const,int const) ; 

__attribute__((used)) static void ZSTD_fillDoubleHashTable(ZSTD_CCtx *cctx, const void *end, const U32 mls)
{
	U32 *const hashLarge = cctx->hashTable;
	U32 const hBitsL = cctx->params.cParams.hashLog;
	U32 *const hashSmall = cctx->chainTable;
	U32 const hBitsS = cctx->params.cParams.chainLog;
	const BYTE *const base = cctx->base;
	const BYTE *ip = base + cctx->nextToUpdate;
	const BYTE *const iend = ((const BYTE *)end) - HASH_READ_SIZE;
	const size_t fastHashFillStep = 3;

	while (ip <= iend) {
		hashSmall[ZSTD_hashPtr(ip, hBitsS, mls)] = (U32)(ip - base);
		hashLarge[ZSTD_hashPtr(ip, hBitsL, 8)] = (U32)(ip - base);
		ip += fastHashFillStep;
	}
}