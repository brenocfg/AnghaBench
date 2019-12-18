#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_11__ {void* dl_havecache; void* dl_havetree; TYPE_5__* dl_dbuf; int /*<<< orphan*/  dl_phys; void* dl_oldfmt; int /*<<< orphan*/  dl_bpobj; int /*<<< orphan*/  dl_object; int /*<<< orphan*/ * dl_os; int /*<<< orphan*/  dl_lock; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_12__ {scalar_t__ doi_type; } ;
typedef  TYPE_2__ dmu_object_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  db_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ DMU_OT_BPOBJ ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_bonus_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_5__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_object_info_from_db (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_deadlist_open(dsl_deadlist_t *dl, objset_t *os, uint64_t object)
{
	dmu_object_info_t doi;

	ASSERT(!dsl_deadlist_is_open(dl));

	mutex_init(&dl->dl_lock, NULL, MUTEX_DEFAULT, NULL);
	dl->dl_os = os;
	dl->dl_object = object;
	VERIFY0(dmu_bonus_hold(os, object, dl, &dl->dl_dbuf));
	dmu_object_info_from_db(dl->dl_dbuf, &doi);
	if (doi.doi_type == DMU_OT_BPOBJ) {
		dmu_buf_rele(dl->dl_dbuf, dl);
		dl->dl_dbuf = NULL;
		dl->dl_oldfmt = B_TRUE;
		VERIFY0(bpobj_open(&dl->dl_bpobj, os, object));
		return;
	}

	dl->dl_oldfmt = B_FALSE;
	dl->dl_phys = dl->dl_dbuf->db_data;
	dl->dl_havetree = B_FALSE;
	dl->dl_havecache = B_FALSE;
}