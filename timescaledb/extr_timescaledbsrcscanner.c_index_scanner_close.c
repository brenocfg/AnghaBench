#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sctx; int /*<<< orphan*/  indexrel; int /*<<< orphan*/  tablerel; } ;
struct TYPE_4__ {int /*<<< orphan*/  lockmode; } ;
typedef  TYPE_2__ InternalScannerCtx ;

/* Variables and functions */
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
index_scanner_close(InternalScannerCtx *ctx)
{
	heap_close(ctx->tablerel, ctx->sctx->lockmode);
	index_close(ctx->indexrel, ctx->sctx->lockmode);
}