#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_8__ {TYPE_1__ fmds_value; } ;
struct TYPE_9__ {TYPE_2__ ms_casesolved; } ;
struct TYPE_10__ {TYPE_3__ mod_stats; } ;
typedef  TYPE_4__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_11__ {scalar_t__ ci_state; int /*<<< orphan*/  ci_uuid; } ;
typedef  TYPE_5__ fmd_case_t ;

/* Variables and functions */
 scalar_t__ FMD_CASE_SOLVED ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,...) ; 

void
fmd_case_solve(fmd_hdl_t *hdl, fmd_case_t *cp)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;

	/*
	 * For ZED, the event was already sent from fmd_case_add_suspect()
	 */

	if (cp->ci_state >= FMD_CASE_SOLVED)
		fmd_hdl_debug(hdl, "case is already solved or closed");

	cp->ci_state = FMD_CASE_SOLVED;

	fmd_hdl_debug(hdl, "case solved (%s)", cp->ci_uuid);
	mp->mod_stats.ms_casesolved.fmds_value.ui64++;
}