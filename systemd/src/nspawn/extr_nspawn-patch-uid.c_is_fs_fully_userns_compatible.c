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
struct statfs {int /*<<< orphan*/  f_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINFMTFS_MAGIC ; 
 int /*<<< orphan*/  BPF_FS_MAGIC ; 
 int /*<<< orphan*/  CGROUP2_SUPER_MAGIC ; 
 int /*<<< orphan*/  CGROUP_SUPER_MAGIC ; 
 int /*<<< orphan*/  DEBUGFS_MAGIC ; 
 int /*<<< orphan*/  DEVPTS_SUPER_MAGIC ; 
 int /*<<< orphan*/  EFIVARFS_MAGIC ; 
 scalar_t__ F_TYPE_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUGETLBFS_MAGIC ; 
 int /*<<< orphan*/  MQUEUE_MAGIC ; 
 int /*<<< orphan*/  PROC_SUPER_MAGIC ; 
 int /*<<< orphan*/  PSTOREFS_MAGIC ; 
 int /*<<< orphan*/  SECURITYFS_MAGIC ; 
 int /*<<< orphan*/  SELINUX_MAGIC ; 
 int /*<<< orphan*/  SMACK_MAGIC ; 
 int /*<<< orphan*/  SYSFS_MAGIC ; 
 int /*<<< orphan*/  TRACEFS_MAGIC ; 
 int /*<<< orphan*/  assert (struct statfs const*) ; 

__attribute__((used)) static int is_fs_fully_userns_compatible(const struct statfs *sfs) {

        assert(sfs);

        return F_TYPE_EQUAL(sfs->f_type, BINFMTFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, CGROUP_SUPER_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, CGROUP2_SUPER_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, DEBUGFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, DEVPTS_SUPER_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, EFIVARFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, HUGETLBFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, MQUEUE_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, PROC_SUPER_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, PSTOREFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, SELINUX_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, SMACK_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, SECURITYFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, BPF_FS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, TRACEFS_MAGIC) ||
               F_TYPE_EQUAL(sfs->f_type, SYSFS_MAGIC);
}