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
struct TYPE_4__ {int /*<<< orphan*/  ds_remap_deadlist; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EQUIV (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dsl_dataset_get_remap_deadlist_object (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 

boolean_t
dsl_dataset_remap_deadlist_exists(dsl_dataset_t *ds)
{
	EQUIV(dsl_deadlist_is_open(&ds->ds_remap_deadlist),
	    dsl_dataset_get_remap_deadlist_object(ds) != 0);
	return (dsl_deadlist_is_open(&ds->ds_remap_deadlist));
}