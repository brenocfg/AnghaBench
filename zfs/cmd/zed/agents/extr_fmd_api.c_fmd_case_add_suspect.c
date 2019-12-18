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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {char const* ci_uuid; TYPE_2__ ci_tv; } ;
typedef  TYPE_1__ fmd_case_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  FM_CLASS ; 
 char const* FM_LIST_SUSPECT_CLASS ; 
 int /*<<< orphan*/  FM_SUSPECT_DIAG_CODE ; 
 int /*<<< orphan*/  FM_SUSPECT_DIAG_TIME ; 
 int /*<<< orphan*/  FM_SUSPECT_FAULT_LIST ; 
 int /*<<< orphan*/  FM_SUSPECT_FAULT_SZ ; 
 int /*<<< orphan*/  FM_SUSPECT_UUID ; 
 int /*<<< orphan*/  FM_SUSPECT_VERSION ; 
 int /*<<< orphan*/  FM_VERSION ; 
 char* fmd_fault_mkcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fmd_nvl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int nvlist_add_int64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int nvlist_add_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_log_die (char*) ; 
 int /*<<< orphan*/  zed_log_fault (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  zfs_agent_post_event (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
fmd_case_add_suspect(fmd_hdl_t *hdl, fmd_case_t *cp, nvlist_t *fault)
{
	nvlist_t *nvl;
	const char *code = fmd_fault_mkcode(fault);
	int64_t tod[2];
	int err = 0;

	/*
	 * payload derived from fmd_protocol_list()
	 */

	(void) gettimeofday(&cp->ci_tv, NULL);
	tod[0] = cp->ci_tv.tv_sec;
	tod[1] = cp->ci_tv.tv_usec;

	nvl = fmd_nvl_alloc(hdl, FMD_SLEEP);

	err |= nvlist_add_uint8(nvl, FM_VERSION, FM_SUSPECT_VERSION);
	err |= nvlist_add_string(nvl, FM_CLASS, FM_LIST_SUSPECT_CLASS);
	err |= nvlist_add_string(nvl, FM_SUSPECT_UUID, cp->ci_uuid);
	err |= nvlist_add_string(nvl, FM_SUSPECT_DIAG_CODE, code);
	err |= nvlist_add_int64_array(nvl, FM_SUSPECT_DIAG_TIME, tod, 2);
	err |= nvlist_add_uint32(nvl, FM_SUSPECT_FAULT_SZ, 1);
	err |= nvlist_add_nvlist_array(nvl, FM_SUSPECT_FAULT_LIST, &fault, 1);

	if (err)
		zed_log_die("failed to populate nvlist");

	zed_log_fault(fault, cp->ci_uuid, code);
	zfs_agent_post_event(FM_LIST_SUSPECT_CLASS, NULL, nvl);

	nvlist_free(nvl);
	nvlist_free(fault);
}