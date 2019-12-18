#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_8__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_9__ {TYPE_1__ fmds_value; } ;
struct TYPE_10__ {TYPE_2__ ms_caseopen; } ;
struct TYPE_11__ {TYPE_3__ mod_stats; } ;
typedef  TYPE_4__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_12__ {int /*<<< orphan*/  ci_uuid; scalar_t__ ci_bufsiz; int /*<<< orphan*/ * ci_bufptr; void* ci_data; int /*<<< orphan*/  ci_flags; int /*<<< orphan*/  ci_state; int /*<<< orphan*/ * ci_mod; } ;
typedef  TYPE_5__ fmd_case_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_CASE_UNSOLVED ; 
 int /*<<< orphan*/  FMD_CF_DIRTY ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* fmd_hdl_zalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_generate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fmd_case_t *
fmd_case_open(fmd_hdl_t *hdl, void *data)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;
	uuid_t uuid;

	fmd_case_t *cp;

	cp = fmd_hdl_zalloc(hdl, sizeof (fmd_case_t), FMD_SLEEP);
	cp->ci_mod = hdl;
	cp->ci_state = FMD_CASE_UNSOLVED;
	cp->ci_flags = FMD_CF_DIRTY;
	cp->ci_data = data;
	cp->ci_bufptr = NULL;
	cp->ci_bufsiz = 0;

	uuid_generate(uuid);
	uuid_unparse(uuid, cp->ci_uuid);

	fmd_hdl_debug(hdl, "case opened (%s)", cp->ci_uuid);
	mp->mod_stats.ms_caseopen.fmds_value.ui64++;

	return (cp);
}