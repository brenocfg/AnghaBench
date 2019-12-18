#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct feature_type_uint64_array_arg {int length; struct feature_type_uint64_array_arg* array; } ;
typedef  size_t spa_feature_t ;
struct TYPE_4__ {struct feature_type_uint64_array_arg** ds_feature; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_5__ {int fi_type; } ;

/* Variables and functions */
#define  ZFEATURE_TYPE_BOOLEAN 129 
#define  ZFEATURE_TYPE_UINT64_ARRAY 128 
 int /*<<< orphan*/  kmem_free (struct feature_type_uint64_array_arg*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_3__* spa_feature_table ; 

__attribute__((used)) static void
unload_zfeature(dsl_dataset_t *ds, spa_feature_t f)
{
	switch (spa_feature_table[f].fi_type) {
	case ZFEATURE_TYPE_BOOLEAN:
		break;
	case ZFEATURE_TYPE_UINT64_ARRAY:
	{
		struct feature_type_uint64_array_arg *ftuaa = ds->ds_feature[f];
		kmem_free(ftuaa->array, ftuaa->length * sizeof (uint64_t));
		kmem_free(ftuaa, sizeof (*ftuaa));
		break;
	}
	default:
		panic("Invalid zfeature type %d", spa_feature_table[f].fi_type);
	}
}