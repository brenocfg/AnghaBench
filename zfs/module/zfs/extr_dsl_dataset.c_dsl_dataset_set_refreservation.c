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
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {char const* ddsqra_name; int /*<<< orphan*/  ddsqra_value; int /*<<< orphan*/  ddsqra_source; } ;
typedef  TYPE_1__ dsl_dataset_set_qr_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_EXTRA_RESERVED ; 
 int /*<<< orphan*/  dsl_dataset_set_refreservation_check ; 
 int /*<<< orphan*/  dsl_dataset_set_refreservation_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dsl_dataset_set_refreservation(const char *dsname, zprop_source_t source,
    uint64_t refreservation)
{
	dsl_dataset_set_qr_arg_t ddsqra;

	ddsqra.ddsqra_name = dsname;
	ddsqra.ddsqra_source = source;
	ddsqra.ddsqra_value = refreservation;

	return (dsl_sync_task(dsname, dsl_dataset_set_refreservation_check,
	    dsl_dataset_set_refreservation_sync, &ddsqra, 0,
	    ZFS_SPACE_CHECK_EXTRA_RESERVED));
}