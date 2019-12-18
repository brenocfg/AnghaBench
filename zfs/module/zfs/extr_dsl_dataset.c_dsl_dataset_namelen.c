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
struct TYPE_4__ {int /*<<< orphan*/  ds_dir; int /*<<< orphan*/  ds_lock; int /*<<< orphan*/  ds_snapname; } ;
typedef  TYPE_1__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_get_snapname (TYPE_1__*) ; 
 scalar_t__ dsl_dir_namelen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int
dsl_dataset_namelen(dsl_dataset_t *ds)
{
	VERIFY0(dsl_dataset_get_snapname(ds));
	mutex_enter(&ds->ds_lock);
	int len = strlen(ds->ds_snapname);
	mutex_exit(&ds->ds_lock);
	/* add '@' if ds is a snap */
	if (len > 0)
		len++;
	len += dsl_dir_namelen(ds->ds_dir);
	return (len);
}