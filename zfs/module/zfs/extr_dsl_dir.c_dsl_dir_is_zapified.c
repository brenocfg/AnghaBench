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
struct TYPE_5__ {int /*<<< orphan*/  dd_dbuf; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_6__ {scalar_t__ doi_type; } ;
typedef  TYPE_2__ dmu_object_info_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ DMU_OTN_ZAP_METADATA ; 
 int /*<<< orphan*/  dmu_object_info_from_db (int /*<<< orphan*/ ,TYPE_2__*) ; 

boolean_t
dsl_dir_is_zapified(dsl_dir_t *dd)
{
	dmu_object_info_t doi;

	dmu_object_info_from_db(dd->dd_dbuf, &doi);
	return (doi.doi_type == DMU_OTN_ZAP_METADATA);
}