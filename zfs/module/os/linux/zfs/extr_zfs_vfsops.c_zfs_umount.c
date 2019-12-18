#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* z_os; int /*<<< orphan*/ * z_arc_prune; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct super_block {TYPE_1__* s_fs_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_2__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  arc_remove_prune_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_disown (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_set_user (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsvfs_free (TYPE_1__*) ; 
 scalar_t__ zfsvfs_teardown (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpl_bdi_destroy (struct super_block*) ; 

int
zfs_umount(struct super_block *sb)
{
	zfsvfs_t *zfsvfs = sb->s_fs_info;
	objset_t *os;

	if (zfsvfs->z_arc_prune != NULL)
		arc_remove_prune_callback(zfsvfs->z_arc_prune);
	VERIFY(zfsvfs_teardown(zfsvfs, B_TRUE) == 0);
	os = zfsvfs->z_os;
	zpl_bdi_destroy(sb);

	/*
	 * z_os will be NULL if there was an error in
	 * attempting to reopen zfsvfs.
	 */
	if (os != NULL) {
		/*
		 * Unset the objset user_ptr.
		 */
		mutex_enter(&os->os_user_ptr_lock);
		dmu_objset_set_user(os, NULL);
		mutex_exit(&os->os_user_ptr_lock);

		/*
		 * Finally release the objset
		 */
		dmu_objset_disown(os, B_TRUE, zfsvfs);
	}

	zfsvfs_free(zfsvfs);
	return (0);
}