#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  Scanner ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 size_t ScannerTypeHeap ; 
 size_t ScannerTypeIndex ; 
 int /*<<< orphan*/ * scanners ; 

__attribute__((used)) static inline Scanner *
scanner_ctx_get_scanner(ScannerCtx *ctx)
{
	if (OidIsValid(ctx->index))
		return &scanners[ScannerTypeIndex];
	else
		return &scanners[ScannerTypeHeap];
}