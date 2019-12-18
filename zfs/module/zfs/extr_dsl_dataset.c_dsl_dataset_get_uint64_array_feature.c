#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct feature_type_uint64_array_arg {int /*<<< orphan*/  length; int /*<<< orphan*/ * array; } ;
typedef  size_t spa_feature_t ;
struct TYPE_5__ {struct feature_type_uint64_array_arg** ds_feature; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int fi_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFEATURE_TYPE_UINT64_ARRAY ; 
 int /*<<< orphan*/  dsl_dataset_feature_is_active (TYPE_1__*,size_t) ; 
 TYPE_2__* spa_feature_table ; 

boolean_t
dsl_dataset_get_uint64_array_feature(dsl_dataset_t *ds, spa_feature_t f,
    uint64_t *outlength, uint64_t **outp)
{
	VERIFY(spa_feature_table[f].fi_type & ZFEATURE_TYPE_UINT64_ARRAY);
	if (!dsl_dataset_feature_is_active(ds, f)) {
		return (B_FALSE);
	}
	struct feature_type_uint64_array_arg *ftuaa = ds->ds_feature[f];
	*outp = ftuaa->array;
	*outlength = ftuaa->length;
	return (B_TRUE);
}