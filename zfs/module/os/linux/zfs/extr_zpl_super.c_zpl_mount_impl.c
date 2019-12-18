#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mnt_osname; } ;
typedef  TYPE_1__ zfs_mnt_t ;
struct super_block {int s_flags; int /*<<< orphan*/ * s_root; } ;
struct file_system_type {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int EBUSY ; 
 struct super_block* ERR_CAST (struct super_block*) ; 
 struct super_block* ERR_PTR (int) ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int SB_ACTIVE ; 
 int SB_RDONLY ; 
 int SB_SILENT ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_anon_super ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int zpl_fill_super (struct super_block*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zpl_test_super ; 

__attribute__((used)) static struct super_block *
zpl_mount_impl(struct file_system_type *fs_type, int flags, zfs_mnt_t *zm)
{
	struct super_block *s;
	objset_t *os;
	int err;

	err = dmu_objset_hold(zm->mnt_osname, FTAG, &os);
	if (err)
		return (ERR_PTR(-err));

	/*
	 * The dsl pool lock must be released prior to calling sget().
	 * It is possible sget() may block on the lock in grab_super()
	 * while deactivate_super() holds that same lock and waits for
	 * a txg sync.  If the dsl_pool lock is held over sget()
	 * this can prevent the pool sync and cause a deadlock.
	 */
	dsl_pool_rele(dmu_objset_pool(os), FTAG);
	s = sget(fs_type, zpl_test_super, set_anon_super, flags, os);
	dsl_dataset_rele(dmu_objset_ds(os), FTAG);

	if (IS_ERR(s))
		return (ERR_CAST(s));

	if (s->s_root == NULL) {
		err = zpl_fill_super(s, zm, flags & SB_SILENT ? 1 : 0);
		if (err) {
			deactivate_locked_super(s);
			return (ERR_PTR(err));
		}
		s->s_flags |= SB_ACTIVE;
	} else if ((flags ^ s->s_flags) & SB_RDONLY) {
		deactivate_locked_super(s);
		return (ERR_PTR(-EBUSY));
	}

	return (s);
}