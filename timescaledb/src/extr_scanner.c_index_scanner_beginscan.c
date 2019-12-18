#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  xs_want_itup; } ;
struct TYPE_9__ {TYPE_6__* index_scan; } ;
struct TYPE_10__ {TYPE_2__ scan; TYPE_1__* sctx; int /*<<< orphan*/  indexrel; int /*<<< orphan*/  tablerel; } ;
struct TYPE_8__ {int /*<<< orphan*/  norderbys; int /*<<< orphan*/  nkeys; int /*<<< orphan*/  scankey; int /*<<< orphan*/  want_itup; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  TYPE_2__ ScanDesc ;
typedef  TYPE_3__ InternalScannerCtx ;

/* Variables and functions */
 int /*<<< orphan*/  SnapshotSelf ; 
 TYPE_6__* index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanDesc
index_scanner_beginscan(InternalScannerCtx *ctx)
{
	ScannerCtx *sctx = ctx->sctx;

	ctx->scan.index_scan =
		index_beginscan(ctx->tablerel, ctx->indexrel, SnapshotSelf, sctx->nkeys, sctx->norderbys);
	ctx->scan.index_scan->xs_want_itup = ctx->sctx->want_itup;
	index_rescan(ctx->scan.index_scan, sctx->scankey, sctx->nkeys, NULL, sctx->norderbys);
	return ctx->scan;
}