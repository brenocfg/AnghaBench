#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os_dsl_dataset; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int /*<<< orphan*/ * dmu_objset_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,void*) ; 

void
dmu_objset_rele_flags(objset_t *os, boolean_t decrypt, void *tag)
{
	ds_hold_flags_t flags = (decrypt) ? DS_HOLD_FLAG_DECRYPT : 0;

	dsl_pool_t *dp = dmu_objset_pool(os);
	dsl_dataset_rele_flags(os->os_dsl_dataset, flags, tag);
	dsl_pool_rele(dp, tag);
}