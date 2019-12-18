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
struct TYPE_5__ {int ps_TupFromTlist; } ;
struct TYPE_6__ {TYPE_1__ ps; } ;
struct TYPE_7__ {scalar_t__ custom_ps; TYPE_2__ ss; } ;
typedef  TYPE_3__ CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  linitial (scalar_t__) ; 

__attribute__((used)) static void
gapfill_rescan(CustomScanState *node)
{
#if PG96
	node->ss.ps.ps_TupFromTlist = false;
#endif
	if (node->custom_ps != NIL)
	{
		ExecReScan(linitial(node->custom_ps));
	}
}