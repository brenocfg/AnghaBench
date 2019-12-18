#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * rep; int /*<<< orphan*/  hufTable; int /*<<< orphan*/  OFTable; int /*<<< orphan*/  MLTable; int /*<<< orphan*/  LLTable; } ;
struct TYPE_10__ {int dictSize; TYPE_2__ entropy; scalar_t__ entropyPresent; scalar_t__ dictContent; int /*<<< orphan*/  dictID; } ;
typedef  TYPE_3__ ZSTD_DDict ;
struct TYPE_8__ {int /*<<< orphan*/ * rep; } ;
struct TYPE_11__ {int litEntropy; int fseEntropy; TYPE_1__ entropy; int /*<<< orphan*/  HUFptr; int /*<<< orphan*/  OFTptr; int /*<<< orphan*/  MLTptr; int /*<<< orphan*/  LLTptr; int /*<<< orphan*/  const* dictEnd; int /*<<< orphan*/  const* previousDstEnd; scalar_t__ vBase; scalar_t__ base; int /*<<< orphan*/  dictID; } ;
typedef  TYPE_4__ ZSTD_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_decompressBegin (TYPE_4__*) ; 

__attribute__((used)) static void ZSTD_refDDict(ZSTD_DCtx *dstDCtx, const ZSTD_DDict *ddict)
{
	ZSTD_decompressBegin(dstDCtx); /* init */
	if (ddict) {		       /* support refDDict on NULL */
		dstDCtx->dictID = ddict->dictID;
		dstDCtx->base = ddict->dictContent;
		dstDCtx->vBase = ddict->dictContent;
		dstDCtx->dictEnd = (const BYTE *)ddict->dictContent + ddict->dictSize;
		dstDCtx->previousDstEnd = dstDCtx->dictEnd;
		if (ddict->entropyPresent) {
			dstDCtx->litEntropy = 1;
			dstDCtx->fseEntropy = 1;
			dstDCtx->LLTptr = ddict->entropy.LLTable;
			dstDCtx->MLTptr = ddict->entropy.MLTable;
			dstDCtx->OFTptr = ddict->entropy.OFTable;
			dstDCtx->HUFptr = ddict->entropy.hufTable;
			dstDCtx->entropy.rep[0] = ddict->entropy.rep[0];
			dstDCtx->entropy.rep[1] = ddict->entropy.rep[1];
			dstDCtx->entropy.rep[2] = ddict->entropy.rep[2];
		} else {
			dstDCtx->litEntropy = 0;
			dstDCtx->fseEntropy = 0;
		}
	}
}