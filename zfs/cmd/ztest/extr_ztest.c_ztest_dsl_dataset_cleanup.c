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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ENOENT ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_destroy_head (char*) ; 
 int dsl_destroy_snapshot (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 

void
ztest_dsl_dataset_cleanup(char *osname, uint64_t id)
{
	char *snap1name;
	char *clone1name;
	char *snap2name;
	char *clone2name;
	char *snap3name;
	int error;

	snap1name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	clone1name = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	snap2name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	clone2name = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);
	snap3name  = umem_alloc(ZFS_MAX_DATASET_NAME_LEN, UMEM_NOFAIL);

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

	error = dsl_destroy_head(clone2name);
	if (error && error != ENOENT)
		fatal(0, "dsl_destroy_head(%s) = %d", clone2name, error);
	error = dsl_destroy_snapshot(snap3name, B_FALSE);
	if (error && error != ENOENT)
		fatal(0, "dsl_destroy_snapshot(%s) = %d", snap3name, error);
	error = dsl_destroy_snapshot(snap2name, B_FALSE);
	if (error && error != ENOENT)
		fatal(0, "dsl_destroy_snapshot(%s) = %d", snap2name, error);
	error = dsl_destroy_head(clone1name);
	if (error && error != ENOENT)
		fatal(0, "dsl_destroy_head(%s) = %d", clone1name, error);
	error = dsl_destroy_snapshot(snap1name, B_FALSE);
	if (error && error != ENOENT)
		fatal(0, "dsl_destroy_snapshot(%s) = %d", snap1name, error);

	umem_free(snap1name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(clone1name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(snap2name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(clone2name, ZFS_MAX_DATASET_NAME_LEN);
	umem_free(snap3name, ZFS_MAX_DATASET_NAME_LEN);
}