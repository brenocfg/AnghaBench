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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  xs_itupdesc; int /*<<< orphan*/  xs_itup; } ;
struct TYPE_8__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  ituple_desc; int /*<<< orphan*/  ituple; } ;
struct TYPE_9__ {TYPE_6__* index_scan; } ;
struct TYPE_10__ {TYPE_2__ tinfo; TYPE_3__ scan; TYPE_1__* sctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  scandirection; } ;
typedef  TYPE_4__ InternalScannerCtx ;

/* Variables and functions */
 int HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getnext (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
index_scanner_getnext(InternalScannerCtx *ctx)
{
	ctx->tinfo.tuple = index_getnext(ctx->scan.index_scan, ctx->sctx->scandirection);
	ctx->tinfo.ituple = ctx->scan.index_scan->xs_itup;
	ctx->tinfo.ituple_desc = ctx->scan.index_scan->xs_itupdesc;
	return HeapTupleIsValid(ctx->tinfo.tuple);
}