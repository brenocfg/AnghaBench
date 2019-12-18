#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_dsl_dataset; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 int dsl_dataset_snap_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

int
dmu_snapshot_lookup(objset_t *os, const char *name, uint64_t *value)
{
	return (dsl_dataset_snap_lookup(os->os_dsl_dataset, name, value));
}