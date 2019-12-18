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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLASS ; 
 int /*<<< orphan*/  FM_FAULT_ASRU ; 
 int /*<<< orphan*/  FM_FAULT_CERTAINTY ; 
 int /*<<< orphan*/  FM_FAULT_FRU ; 
 int /*<<< orphan*/  FM_FAULT_RESOURCE ; 
 int /*<<< orphan*/  FM_FAULT_VERSION ; 
 int /*<<< orphan*/  FM_VERSION ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zed_log_die (char*,...) ; 

nvlist_t *
fmd_nvl_create_fault(fmd_hdl_t *hdl, const char *class, uint8_t certainty,
    nvlist_t *asru, nvlist_t *fru, nvlist_t *resource)
{
	nvlist_t *nvl;
	int err = 0;

	if (nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0) != 0)
		zed_log_die("failed to xalloc fault nvlist");

	err |= nvlist_add_uint8(nvl, FM_VERSION, FM_FAULT_VERSION);
	err |= nvlist_add_string(nvl, FM_CLASS, class);
	err |= nvlist_add_uint8(nvl, FM_FAULT_CERTAINTY, certainty);

	if (asru != NULL)
		err |= nvlist_add_nvlist(nvl, FM_FAULT_ASRU, asru);
	if (fru != NULL)
		err |= nvlist_add_nvlist(nvl, FM_FAULT_FRU, fru);
	if (resource != NULL)
		err |= nvlist_add_nvlist(nvl, FM_FAULT_RESOURCE, resource);

	if (err)
		zed_log_die("failed to populate nvlist: %s\n", strerror(err));

	return (nvl);
}