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
typedef  int uint64_t ;
struct feature_type_uint64_array_arg {int /*<<< orphan*/  array; scalar_t__ length; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int ds_object; struct feature_type_uint64_array_arg** ds_feature; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 size_t SPA_FEATURE_REDACTED_DATASETS ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsl_dataset_activate_feature (int,size_t,struct feature_type_uint64_array_arg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_alloc (int,int /*<<< orphan*/ ) ; 
 struct feature_type_uint64_array_arg* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

void
dsl_dataset_activate_redaction(dsl_dataset_t *ds, uint64_t *redact_snaps,
    uint64_t num_redact_snaps, dmu_tx_t *tx)
{
	uint64_t dsobj = ds->ds_object;
	struct feature_type_uint64_array_arg *ftuaa =
	    kmem_zalloc(sizeof (*ftuaa), KM_SLEEP);
	ftuaa->length = (int64_t)num_redact_snaps;
	if (num_redact_snaps > 0) {
		ftuaa->array = kmem_alloc(num_redact_snaps * sizeof (uint64_t),
		    KM_SLEEP);
		bcopy(redact_snaps, ftuaa->array, num_redact_snaps *
		    sizeof (uint64_t));
	}
	dsl_dataset_activate_feature(dsobj, SPA_FEATURE_REDACTED_DATASETS,
	    ftuaa, tx);
	ds->ds_feature[SPA_FEATURE_REDACTED_DATASETS] = ftuaa;
}