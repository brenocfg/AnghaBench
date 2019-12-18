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
struct TYPE_4__ {int /*<<< orphan*/  heap_scan; } ;
struct TYPE_5__ {TYPE_1__ scan; } ;
typedef  TYPE_2__ InternalScannerCtx ;

/* Variables and functions */
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
heap_scanner_endscan(InternalScannerCtx *ctx)
{
	heap_endscan(ctx->scan.heap_scan);
}