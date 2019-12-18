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
typedef  unsigned long long int64_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 

int64_t
fmd_prop_get_int64(fmd_hdl_t *hdl, const char *name)
{
	/*
	 * These can be looked up in mp->modinfo->fmdi_props
	 * For now we just hard code for phase 2. In the
	 * future, there can be a ZED based override.
	 */
	if (strcmp(name, "remove_timeout") == 0)
		return (15ULL * 1000ULL * 1000ULL * 1000ULL);	/* 15 sec */

	if (strcmp(name, "io_T") == 0 || strcmp(name, "checksum_T") == 0)
		return (1000ULL * 1000ULL * 1000ULL * 600ULL);	/* 10 min */

	return (0);
}