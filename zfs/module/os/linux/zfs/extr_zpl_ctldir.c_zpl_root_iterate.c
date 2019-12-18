#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pos; } ;
typedef  TYPE_1__ zpl_dir_context_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/ * ITOZSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFSCTL_INO_SHARES ; 
 int /*<<< orphan*/  ZFSCTL_INO_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_SHAREDIR_NAME ; 
 int /*<<< orphan*/  ZFS_SNAPDIR_NAME ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpl_dir_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpl_dir_emit_dots (struct file*,TYPE_1__*) ; 

__attribute__((used)) static int
zpl_root_iterate(struct file *filp, zpl_dir_context_t *ctx)
{
	zfsvfs_t *zfsvfs = ITOZSB(file_inode(filp));
	int error = 0;

	ZFS_ENTER(zfsvfs);

	if (!zpl_dir_emit_dots(filp, ctx))
		goto out;

	if (ctx->pos == 2) {
		if (!zpl_dir_emit(ctx, ZFS_SNAPDIR_NAME,
		    strlen(ZFS_SNAPDIR_NAME), ZFSCTL_INO_SNAPDIR, DT_DIR))
			goto out;

		ctx->pos++;
	}

	if (ctx->pos == 3) {
		if (!zpl_dir_emit(ctx, ZFS_SHAREDIR_NAME,
		    strlen(ZFS_SHAREDIR_NAME), ZFSCTL_INO_SHARES, DT_DIR))
			goto out;

		ctx->pos++;
	}
out:
	ZFS_EXIT(zfsvfs);

	return (error);
}