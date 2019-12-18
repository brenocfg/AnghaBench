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
typedef  size_t spa_feature_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ds_feature; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfeature_active (size_t,int /*<<< orphan*/ ) ; 

boolean_t
dsl_dataset_feature_is_active(dsl_dataset_t *ds, spa_feature_t f)
{
	return (zfeature_active(f, ds->ds_feature[f]));
}