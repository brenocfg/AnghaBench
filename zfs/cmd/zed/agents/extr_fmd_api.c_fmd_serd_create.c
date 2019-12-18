#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  hrtime_t ;
struct TYPE_2__ {int /*<<< orphan*/  mod_serds; } ;
typedef  TYPE_1__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  fmd_serd_eng_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fmd_serd_eng_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*) ; 

void
fmd_serd_create(fmd_hdl_t *hdl, const char *name, uint_t n, hrtime_t t)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;

	if (fmd_serd_eng_lookup(&mp->mod_serds, name) != NULL) {
		zed_log_msg(LOG_ERR, "failed to create SERD engine '%s': "
		    " name already exists", name);
		return;
	}

	(void) fmd_serd_eng_insert(&mp->mod_serds, name, n, t);
}