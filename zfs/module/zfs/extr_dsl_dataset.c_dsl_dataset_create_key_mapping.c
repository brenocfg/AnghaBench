#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dd_crypto_obj; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_key_mapping; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int spa_keystore_create_mapping (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

int
dsl_dataset_create_key_mapping(dsl_dataset_t *ds)
{
	dsl_dir_t *dd = ds->ds_dir;

	if (dd->dd_crypto_obj == 0)
		return (0);

	return (spa_keystore_create_mapping(dd->dd_pool->dp_spa,
	    ds, ds, &ds->ds_key_mapping));
}