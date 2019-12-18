#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ds_fsid_guid; int /*<<< orphan*/ * ds_owner; } ;
typedef  TYPE_1__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unique_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_dataset_evict_sync(void *dbu)
{
	dsl_dataset_t *ds = dbu;

	ASSERT(ds->ds_owner == NULL);

	unique_remove(ds->ds_fsid_guid);
}