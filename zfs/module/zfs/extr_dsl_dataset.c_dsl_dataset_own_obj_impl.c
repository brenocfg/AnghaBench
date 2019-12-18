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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_dataset_hold_obj_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dsl_dataset_tryown (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_dataset_own_obj_impl(dsl_pool_t *dp, uint64_t dsobj, ds_hold_flags_t flags,
    void *tag, boolean_t override, dsl_dataset_t **dsp)
{
	int err = dsl_dataset_hold_obj_flags(dp, dsobj, flags, tag, dsp);
	if (err != 0)
		return (err);
	if (!dsl_dataset_tryown(*dsp, tag, override)) {
		dsl_dataset_rele_flags(*dsp, flags, tag);
		*dsp = NULL;
		return (SET_ERROR(EBUSY));
	}
	return (0);
}