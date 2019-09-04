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
struct TYPE_3__ {int /*<<< orphan*/  ictx; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ScanIterator ;

/* Variables and functions */
 int /*<<< orphan*/  ts_scanner_end_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ts_scan_iterator_close(ScanIterator *iterator)
{
	ts_scanner_end_scan(&iterator->ctx, &iterator->ictx);
}