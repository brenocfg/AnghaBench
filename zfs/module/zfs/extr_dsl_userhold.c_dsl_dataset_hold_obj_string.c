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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_strtonum (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_dataset_hold_obj_string(dsl_pool_t *dp, const char *dsobj, void *tag,
    dsl_dataset_t **dsp)
{
	return (dsl_dataset_hold_obj(dp, zfs_strtonum(dsobj, NULL), tag, dsp));
}