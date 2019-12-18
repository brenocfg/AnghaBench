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
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  blkptr_cb_t ;

/* Variables and functions */
 int traverse_dataset_resume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 

int
traverse_dataset(dsl_dataset_t *ds, uint64_t txg_start,
    int flags, blkptr_cb_t func, void *arg)
{
	return (traverse_dataset_resume(ds, txg_start, NULL, flags, func, arg));
}