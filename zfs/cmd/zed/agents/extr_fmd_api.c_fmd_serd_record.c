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
typedef  int /*<<< orphan*/  fmd_serd_eng_t ;
struct TYPE_4__ {int /*<<< orphan*/  mod_serds; } ;
typedef  TYPE_1__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/  ev_hrt; } ;
typedef  TYPE_2__ fmd_event_t ;

/* Variables and functions */
 int FMD_B_FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * fmd_serd_eng_lookup (int /*<<< orphan*/ *,char const*) ; 
 int fmd_serd_eng_record (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*) ; 

int
fmd_serd_record(fmd_hdl_t *hdl, const char *name, fmd_event_t *ep)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;
	fmd_serd_eng_t *sgp;
	int err;

	if ((sgp = fmd_serd_eng_lookup(&mp->mod_serds, name)) == NULL) {
		zed_log_msg(LOG_ERR, "failed to add record to SERD engine '%s'",
		    name);
		return (FMD_B_FALSE);
	}
	err = fmd_serd_eng_record(sgp, ep->ev_hrt);

	return (err);
}