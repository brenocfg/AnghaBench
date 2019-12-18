#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  drc_raw; int /*<<< orphan*/  drc_newsnapobj; int /*<<< orphan*/ * drc_guid_to_ds_map; int /*<<< orphan*/  drc_tofs; int /*<<< orphan*/  drc_keynvl; scalar_t__ drc_newfs; void* drc_owner; } ;
typedef  TYPE_1__ dmu_recv_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_ds_to_guidmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_recv_cleanup_ds (TYPE_1__*) ; 
 int dmu_recv_existing_end (TYPE_1__*) ; 
 int dmu_recv_new_end (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 

int
dmu_recv_end(dmu_recv_cookie_t *drc, void *owner)
{
	int error;

	drc->drc_owner = owner;

	if (drc->drc_newfs)
		error = dmu_recv_new_end(drc);
	else
		error = dmu_recv_existing_end(drc);

	if (error != 0) {
		dmu_recv_cleanup_ds(drc);
		nvlist_free(drc->drc_keynvl);
	} else if (drc->drc_guid_to_ds_map != NULL) {
		(void) add_ds_to_guidmap(drc->drc_tofs, drc->drc_guid_to_ds_map,
		    drc->drc_newsnapobj, drc->drc_raw);
	}
	return (error);
}