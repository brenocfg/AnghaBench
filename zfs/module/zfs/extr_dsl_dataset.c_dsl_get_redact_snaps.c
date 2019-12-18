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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_REDACTED_DATASETS ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ dsl_dataset_get_uint64_array_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fnvlist_add_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_get_redact_snaps(dsl_dataset_t *ds, nvlist_t *propval)
{
	uint64_t nsnaps;
	uint64_t *snaps;
	if (dsl_dataset_get_uint64_array_feature(ds,
	    SPA_FEATURE_REDACTED_DATASETS, &nsnaps, &snaps)) {
		fnvlist_add_uint64_array(propval, ZPROP_VALUE, snaps,
		    nsnaps);
	}
}