#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pos; } ;
typedef  TYPE_1__ zpl_dir_context_t ;
struct TYPE_10__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 TYPE_2__* ITOZSB (int /*<<< orphan*/ ) ; 
 int MAXNAMELEN ; 
 scalar_t__ ZFSCTL_INO_SHARES ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ ) ; 
 int dmu_snapshot_list_next (int /*<<< orphan*/ ,int,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zpl_dir_emit (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpl_dir_emit_dots (struct file*,TYPE_1__*) ; 

__attribute__((used)) static int
zpl_snapdir_iterate(struct file *filp, zpl_dir_context_t *ctx)
{
	zfsvfs_t *zfsvfs = ITOZSB(file_inode(filp));
	fstrans_cookie_t cookie;
	char snapname[MAXNAMELEN];
	boolean_t case_conflict;
	uint64_t id, pos;
	int error = 0;

	ZFS_ENTER(zfsvfs);
	cookie = spl_fstrans_mark();

	if (!zpl_dir_emit_dots(filp, ctx))
		goto out;

	pos = ctx->pos;
	while (error == 0) {
		dsl_pool_config_enter(dmu_objset_pool(zfsvfs->z_os), FTAG);
		error = -dmu_snapshot_list_next(zfsvfs->z_os, MAXNAMELEN,
		    snapname, &id, &pos, &case_conflict);
		dsl_pool_config_exit(dmu_objset_pool(zfsvfs->z_os), FTAG);
		if (error)
			goto out;

		if (!zpl_dir_emit(ctx, snapname, strlen(snapname),
		    ZFSCTL_INO_SHARES - id, DT_DIR))
			goto out;

		ctx->pos = pos;
	}
out:
	spl_fstrans_unmark(cookie);
	ZFS_EXIT(zfsvfs);

	if (error == -ENOENT)
		return (0);

	return (error);
}