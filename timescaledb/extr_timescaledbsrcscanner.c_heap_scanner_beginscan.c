#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  heap_scan; } ;
struct TYPE_8__ {TYPE_2__ scan; int /*<<< orphan*/  tablerel; TYPE_1__* sctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  scankey; int /*<<< orphan*/  nkeys; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  TYPE_2__ ScanDesc ;
typedef  TYPE_3__ InternalScannerCtx ;

/* Variables and functions */
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  heap_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanDesc
heap_scanner_beginscan(InternalScannerCtx *ctx)
{
	ScannerCtx *sctx = ctx->sctx;

	ctx->scan.heap_scan = heap_beginscan(ctx->tablerel, SnapshotSelf, sctx->nkeys, sctx->scankey);
	return ctx->scan;
}