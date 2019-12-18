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
struct TYPE_3__ {char* zd_name; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_objset_clone (char*,char*) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmu_objset_snapshot_one (char*,scalar_t__) ; 
 int dsl_dataset_promote (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 
 int ztest_dmu_objset_own (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ztest_dsl_dataset_cleanup (char*,scalar_t__) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 int /*<<< orphan*/  ztest_record_enospc (int /*<<< orphan*/ ) ; 

void
ztest_dsl_dataset_promote_busy(ztest_ds_t *zd, uint64_t id)
{
	objset_t *os;
	char *snap1name;
	char *clone1name;
	char *snap2name;
	char *clone2name;
	char *snap3name;
	char *osname = zd->zd_name;
	int error;

	snap1name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	clone1name = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	snap2name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	clone2name = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	snap3name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);

	(void) pthread_rwlock_rdlock(&ztest_name_lock);

	ztest_dsl_dataset_cleanup(osname, id);

	(void) snprintf(snap1name, ZFS_MAX_DATASET_NAME_LEN,
	    "%s@s1_%llu", osname, (u_longlong_t)id);
	(void) snprintf(clone1name, ZFS_MAX_DATASET_NAME_LEN,
	    "%s/c1_%llu", osname, (u_longlong_t)id);
	(void) snprintf(snap2name, ZFS_MAX_DATASET_NAME_LEN,
	    "%s@s2_%llu", clone1name, (u_longlong_t)id);
	(void) snprintf(clone2name, ZFS_MAX_DATASET_NAME_LEN,
	    "%s/c2_%llu", osname, (u_longlong_t)id);
	(void) snprintf(snap3name, ZFS_MAX_DATASET_NAME_LEN,
	    "%s@s3_%llu", clone1name, (u_longlong_t)id);

	error = dmu_objset_snapshot_one(osname, strchr(snap1name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_take_snapshot(%s) = %d", snap1name, error);
	}

	error = dmu_objset_clone(clone1name, snap1name);
	if (error) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_objset_create(%s) = %d", clone1name, error);
	}

	error = dmu_objset_snapshot_one(clone1name, strchr(snap2name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_open_snapshot(%s) = %d", snap2name, error);
	}

	error = dmu_objset_snapshot_one(clone1name, strchr(snap3name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_open_snapshot(%s) = %d", snap3name, error);
	}

	error = dmu_objset_clone(clone2name, snap3name);
	if (error) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_objset_create(%s) = %d", clone2name, error);
	}

	error = ztest_dmu_objset_own(snap2name, DMU_OST_ANY, B_TRUE, B_TRUE,
	    FTAG, &os);
	if (error)
		fatal(0, "dmu_objset_own(%s) = %d", snap2name, error);
	error = dsl_dataset_promote(clone2name, NULL);
	if (error == ENOSPC) {
		dmu_objset_disown(os, B_TRUE, FTAG);
		ztest_record_enospc(FTAG);
		goto out;
	}
	if (error != EBUSY)
		fatal(0, "dsl_dataset_promote(%s), %d, not EBUSY", clone2name,
		    error);
	dmu_objset_disown(os, B_TRUE, FTAG);

out:
	ztest_dsl_dataset_cleanup(osname, id);

	(void) pthread_rwlock_unlock(&ztest_name_lock);

	umem_free(snap1name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(clone1name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(snap2name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(clone2name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(snap3name, ZFS_MAX_DATASET_NAME_LEN);
}