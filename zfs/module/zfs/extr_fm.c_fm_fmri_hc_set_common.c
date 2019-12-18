#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct TYPE_6__ {TYPE_2__ fmri_set_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_FMRI_AUTHORITY ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME_HC ; 
 int FM_HC_SCHEME_VERSION ; 
 int /*<<< orphan*/  FM_VERSION ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 
 TYPE_3__ erpt_kstat_data ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fm_fmri_hc_set_common(nvlist_t *fmri, int version, const nvlist_t *auth)
{
	if (version != FM_HC_SCHEME_VERSION) {
		atomic_inc_64(&erpt_kstat_data.fmri_set_failed.value.ui64);
		return (0);
	}

	if (nvlist_add_uint8(fmri, FM_VERSION, version) != 0 ||
	    nvlist_add_string(fmri, FM_FMRI_SCHEME, FM_FMRI_SCHEME_HC) != 0) {
		atomic_inc_64(&erpt_kstat_data.fmri_set_failed.value.ui64);
		return (0);
	}

	if (auth != NULL && nvlist_add_nvlist(fmri, FM_FMRI_AUTHORITY,
	    (nvlist_t *)auth) != 0) {
		atomic_inc_64(&erpt_kstat_data.fmri_set_failed.value.ui64);
		return (0);
	}

	return (1);
}