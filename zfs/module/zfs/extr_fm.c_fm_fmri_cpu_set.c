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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct TYPE_6__ {TYPE_2__ fmri_set_failed; } ;

/* Variables and functions */
 int CPU_SCHEME_VERSION1 ; 
 int /*<<< orphan*/  FM_FMRI_AUTHORITY ; 
 int /*<<< orphan*/  FM_FMRI_CPU_ID ; 
 int /*<<< orphan*/  FM_FMRI_CPU_MASK ; 
 int /*<<< orphan*/  FM_FMRI_CPU_SERIAL_ID ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME ; 
 char* FM_FMRI_SCHEME_CPU ; 
 int /*<<< orphan*/  FM_VERSION ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 
 TYPE_3__ erpt_kstat_data ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
fm_fmri_cpu_set(nvlist_t *fmri_cpu, int version, const nvlist_t *auth,
    uint32_t cpu_id, uint8_t *cpu_maskp, const char *serial_idp)
{
	uint64_t *failedp = &erpt_kstat_data.fmri_set_failed.value.ui64;

	if (version < CPU_SCHEME_VERSION1) {
		atomic_inc_64(failedp);
		return;
	}

	if (nvlist_add_uint8(fmri_cpu, FM_VERSION, version) != 0) {
		atomic_inc_64(failedp);
		return;
	}

	if (nvlist_add_string(fmri_cpu, FM_FMRI_SCHEME,
	    FM_FMRI_SCHEME_CPU) != 0) {
		atomic_inc_64(failedp);
		return;
	}

	if (auth != NULL && nvlist_add_nvlist(fmri_cpu, FM_FMRI_AUTHORITY,
	    (nvlist_t *)auth) != 0)
		atomic_inc_64(failedp);

	if (nvlist_add_uint32(fmri_cpu, FM_FMRI_CPU_ID, cpu_id) != 0)
		atomic_inc_64(failedp);

	if (cpu_maskp != NULL && nvlist_add_uint8(fmri_cpu, FM_FMRI_CPU_MASK,
	    *cpu_maskp) != 0)
		atomic_inc_64(failedp);

	if (serial_idp == NULL || nvlist_add_string(fmri_cpu,
	    FM_FMRI_CPU_SERIAL_ID, (char *)serial_idp) != 0)
			atomic_inc_64(failedp);
}