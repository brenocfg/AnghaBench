#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_8__ {TYPE_1__* ds_dir; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_unique_bytes; } ;

/* Variables and functions */
 TYPE_5__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dir_get_used (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

uint64_t
dsl_get_used(dsl_dataset_t *ds)
{
	if (ds->ds_is_snapshot) {
		return (dsl_dataset_phys(ds)->ds_unique_bytes);
	} else {
		dsl_dir_t *dd = ds->ds_dir;
		mutex_enter(&dd->dd_lock);
		uint64_t val = dsl_dir_get_used(dd);
		mutex_exit(&dd->dd_lock);
		return (val);
	}
}