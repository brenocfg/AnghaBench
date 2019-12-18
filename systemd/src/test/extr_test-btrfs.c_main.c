#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ts ;
typedef  int /*<<< orphan*/  bs ;
struct TYPE_8__ {unsigned long long referenced; unsigned long long exclusive; unsigned long long referenced_max; unsigned long long exclusive_max; } ;
struct TYPE_7__ {int read_only; int /*<<< orphan*/  otime; } ;
typedef  TYPE_1__ BtrfsSubvolInfo ;
typedef  TYPE_2__ BtrfsQuotaInfo ;

/* Variables and functions */
 int BTRFS_REMOVE_QUOTA ; 
 int BTRFS_REMOVE_RECURSIVE ; 
 int BTRFS_SNAPSHOT_FALLBACK_COPY ; 
 int BTRFS_SNAPSHOT_QUOTA ; 
 int BTRFS_SNAPSHOT_READ_ONLY ; 
 int BTRFS_SNAPSHOT_RECURSIVE ; 
 int FORMAT_BYTES_MAX ; 
 int FORMAT_TIMESTAMP_MAX ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  WRITE_STRING_FILE_CREATE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int btrfs_qgroup_get_quota (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int btrfs_qgroup_get_quota_fd (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int btrfs_qgroup_set_limit (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int btrfs_subvol_auto_qgroup (char*,int /*<<< orphan*/ ,int) ; 
 int btrfs_subvol_get_info_fd (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int btrfs_subvol_get_read_only_fd (int) ; 
 int btrfs_subvol_get_subtree_quota (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int btrfs_subvol_make (char*) ; 
 int btrfs_subvol_remove (char*,int) ; 
 int btrfs_subvol_set_subtree_quota_limit (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int btrfs_subvol_snapshot (char*,char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  format_bytes (char*,int,unsigned long long) ; 
 int /*<<< orphan*/  format_timestamp (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mkdir (char*,int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 
 int write_string_file (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yes_no (int) ; 

int main(int argc, char *argv[]) {
        BtrfsQuotaInfo quota;
        int r, fd;

        fd = open("/", O_RDONLY|O_CLOEXEC|O_DIRECTORY);
        if (fd < 0)
                log_error_errno(errno, "Failed to open root directory: %m");
        else {
                char ts[FORMAT_TIMESTAMP_MAX], bs[FORMAT_BYTES_MAX];
                BtrfsSubvolInfo info;

                r = btrfs_subvol_get_info_fd(fd, 0, &info);
                if (r < 0)
                        log_error_errno(r, "Failed to get subvolume info: %m");
                else {
                        log_info("otime: %s", format_timestamp(ts, sizeof(ts), info.otime));
                        log_info("read-only (search): %s", yes_no(info.read_only));
                }

                r = btrfs_qgroup_get_quota_fd(fd, 0, &quota);
                if (r < 0)
                        log_error_errno(r, "Failed to get quota info: %m");
                else {
                        log_info("referenced: %s", strna(format_bytes(bs, sizeof(bs), quota.referenced)));
                        log_info("exclusive: %s", strna(format_bytes(bs, sizeof(bs), quota.exclusive)));
                        log_info("referenced_max: %s", strna(format_bytes(bs, sizeof(bs), quota.referenced_max)));
                        log_info("exclusive_max: %s", strna(format_bytes(bs, sizeof(bs), quota.exclusive_max)));
                }

                r = btrfs_subvol_get_read_only_fd(fd);
                if (r < 0)
                        log_error_errno(r, "Failed to get read only flag: %m");
                else
                        log_info("read-only (ioctl): %s", yes_no(r));

                safe_close(fd);
        }

        r = btrfs_subvol_make("/xxxtest");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = write_string_file("/xxxtest/afile", "ljsadhfljasdkfhlkjdsfha", WRITE_STRING_FILE_CREATE);
        if (r < 0)
                log_error_errno(r, "Failed to write file: %m");

        r = btrfs_subvol_snapshot("/xxxtest", "/xxxtest2", 0);
        if (r < 0)
                log_error_errno(r, "Failed to make snapshot: %m");

        r = btrfs_subvol_snapshot("/xxxtest", "/xxxtest3", BTRFS_SNAPSHOT_READ_ONLY);
        if (r < 0)
                log_error_errno(r, "Failed to make snapshot: %m");

        r = btrfs_subvol_remove("/xxxtest", BTRFS_REMOVE_QUOTA);
        if (r < 0)
                log_error_errno(r, "Failed to remove subvolume: %m");

        r = btrfs_subvol_remove("/xxxtest2", BTRFS_REMOVE_QUOTA);
        if (r < 0)
                log_error_errno(r, "Failed to remove subvolume: %m");

        r = btrfs_subvol_remove("/xxxtest3", BTRFS_REMOVE_QUOTA);
        if (r < 0)
                log_error_errno(r, "Failed to remove subvolume: %m");

        r = btrfs_subvol_snapshot("/etc", "/etc2", BTRFS_SNAPSHOT_READ_ONLY|BTRFS_SNAPSHOT_FALLBACK_COPY);
        if (r < 0)
                log_error_errno(r, "Failed to make snapshot: %m");

        r = btrfs_subvol_remove("/etc2", BTRFS_REMOVE_QUOTA);
        if (r < 0)
                log_error_errno(r, "Failed to remove subvolume: %m");

        r = btrfs_subvol_make("/xxxrectest");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = btrfs_subvol_make("/xxxrectest/xxxrectest2");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = btrfs_subvol_make("/xxxrectest/xxxrectest3");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = btrfs_subvol_make("/xxxrectest/xxxrectest3/sub");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        if (mkdir("/xxxrectest/dir", 0755) < 0)
                log_error_errno(errno, "Failed to make directory: %m");

        r = btrfs_subvol_make("/xxxrectest/dir/xxxrectest4");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        if (mkdir("/xxxrectest/dir/xxxrectest4/dir", 0755) < 0)
                log_error_errno(errno, "Failed to make directory: %m");

        r = btrfs_subvol_make("/xxxrectest/dir/xxxrectest4/dir/xxxrectest5");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        if (mkdir("/xxxrectest/mnt", 0755) < 0)
                log_error_errno(errno, "Failed to make directory: %m");

        r = btrfs_subvol_snapshot("/xxxrectest", "/xxxrectest2", BTRFS_SNAPSHOT_RECURSIVE);
        if (r < 0)
                log_error_errno(r, "Failed to snapshot subvolume: %m");

        r = btrfs_subvol_remove("/xxxrectest", BTRFS_REMOVE_QUOTA|BTRFS_REMOVE_RECURSIVE);
        if (r < 0)
                log_error_errno(r, "Failed to recursively remove subvolume: %m");

        r = btrfs_subvol_remove("/xxxrectest2", BTRFS_REMOVE_QUOTA|BTRFS_REMOVE_RECURSIVE);
        if (r < 0)
                log_error_errno(r, "Failed to recursively remove subvolume: %m");

        r = btrfs_subvol_make("/xxxquotatest");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = btrfs_subvol_auto_qgroup("/xxxquotatest", 0, true);
        if (r < 0)
                log_error_errno(r, "Failed to set up auto qgroup: %m");

        r = btrfs_subvol_make("/xxxquotatest/beneath");
        if (r < 0)
                log_error_errno(r, "Failed to make subvolume: %m");

        r = btrfs_subvol_auto_qgroup("/xxxquotatest/beneath", 0, false);
        if (r < 0)
                log_error_errno(r, "Failed to set up auto qgroup: %m");

        r = btrfs_qgroup_set_limit("/xxxquotatest/beneath", 0, 4ULL * 1024 * 1024 * 1024);
        if (r < 0)
                log_error_errno(r, "Failed to set up quota limit: %m");

        r = btrfs_subvol_set_subtree_quota_limit("/xxxquotatest", 0, 5ULL * 1024 * 1024 * 1024);
        if (r < 0)
                log_error_errno(r, "Failed to set up quota limit: %m");

        r = btrfs_subvol_snapshot("/xxxquotatest", "/xxxquotatest2", BTRFS_SNAPSHOT_RECURSIVE|BTRFS_SNAPSHOT_QUOTA);
        if (r < 0)
                log_error_errno(r, "Failed to setup snapshot: %m");

        r = btrfs_qgroup_get_quota("/xxxquotatest2/beneath", 0, &quota);
        if (r < 0)
                log_error_errno(r, "Failed to query quota: %m");

        assert_se(quota.referenced_max == 4ULL * 1024 * 1024 * 1024);

        r = btrfs_subvol_get_subtree_quota("/xxxquotatest2", 0, &quota);
        if (r < 0)
                log_error_errno(r, "Failed to query quota: %m");

        assert_se(quota.referenced_max == 5ULL * 1024 * 1024 * 1024);

        r = btrfs_subvol_remove("/xxxquotatest", BTRFS_REMOVE_QUOTA|BTRFS_REMOVE_RECURSIVE);
        if (r < 0)
                log_error_errno(r, "Failed remove subvolume: %m");

        r = btrfs_subvol_remove("/xxxquotatest2", BTRFS_REMOVE_QUOTA|BTRFS_REMOVE_RECURSIVE);
        if (r < 0)
                log_error_errno(r, "Failed remove subvolume: %m");

        return 0;
}