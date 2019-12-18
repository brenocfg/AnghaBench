#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dd_crypto_obj; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_8__ {int /*<<< orphan*/  ds_object; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  spa_keystore_remove_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

void
dsl_dataset_remove_key_mapping(dsl_dataset_t *ds)
{
	dsl_dir_t *dd = ds->ds_dir;

	if (dd == NULL || dd->dd_crypto_obj == 0)
		return;

	(void) spa_keystore_remove_mapping(dd->dd_pool->dp_spa,
	    ds->ds_object, ds);
}