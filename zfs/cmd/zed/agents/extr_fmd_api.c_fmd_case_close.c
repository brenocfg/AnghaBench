#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_17__ {TYPE_4__ fmds_value; } ;
struct TYPE_14__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_15__ {TYPE_2__ fmds_value; } ;
struct TYPE_18__ {TYPE_5__ ms_caseclosed; TYPE_3__ ms_caseopen; } ;
struct TYPE_19__ {TYPE_6__ mod_stats; TYPE_1__* mod_info; } ;
typedef  TYPE_7__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* fmdo_close ) (int /*<<< orphan*/ *,TYPE_9__*) ;} ;
typedef  TYPE_8__ fmd_hdl_ops_t ;
struct TYPE_21__ {scalar_t__ ci_bufsiz; struct TYPE_21__* ci_bufptr; int /*<<< orphan*/  ci_uuid; } ;
typedef  TYPE_9__ fmd_case_t ;
struct TYPE_13__ {TYPE_8__* fmdi_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_9__*) ; 

void
fmd_case_close(fmd_hdl_t *hdl, fmd_case_t *cp)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;
	const fmd_hdl_ops_t *ops = mp->mod_info->fmdi_ops;

	fmd_hdl_debug(hdl, "case closed (%s)", cp->ci_uuid);

	if (ops->fmdo_close != NULL)
		ops->fmdo_close(hdl, cp);

	mp->mod_stats.ms_caseopen.fmds_value.ui64--;
	mp->mod_stats.ms_caseclosed.fmds_value.ui64++;

	if (cp->ci_bufptr != NULL && cp->ci_bufsiz > 0)
		fmd_hdl_free(hdl, cp->ci_bufptr, cp->ci_bufsiz);

	fmd_hdl_free(hdl, cp, sizeof (fmd_case_t));
}