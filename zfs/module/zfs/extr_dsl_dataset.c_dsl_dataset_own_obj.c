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

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int dsl_dataset_own_obj_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
dsl_dataset_own_obj(dsl_pool_t *dp, uint64_t dsobj, ds_hold_flags_t flags,
    void *tag, dsl_dataset_t **dsp)
{
	return (dsl_dataset_own_obj_impl(dp, dsobj, flags, tag, B_FALSE, dsp));
}