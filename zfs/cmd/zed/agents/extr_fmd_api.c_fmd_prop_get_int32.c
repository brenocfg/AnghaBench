#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 

int32_t
fmd_prop_get_int32(fmd_hdl_t *hdl, const char *name)
{
	/*
	 * These can be looked up in mp->modinfo->fmdi_props
	 * For now we just hard code for phase 2. In the
	 * future, there can be a ZED based override.
	 */
	if (strcmp(name, "spare_on_remove") == 0)
		return (1);

	if (strcmp(name, "io_N") == 0 || strcmp(name, "checksum_N") == 0)
		return (10);	/* N = 10 events */

	return (0);
}