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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  blkid_probe ;

/* Variables and functions */
 int /*<<< orphan*/  BLKID_PARTS_ENTRY_DETAILS ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int blkid_do_fullprobe (int /*<<< orphan*/ ) ; 
 int blkid_do_safeprobe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkid_probe_enable_partitions (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blkid_probe_enable_superblocks (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blkid_probe_get_fd (int /*<<< orphan*/ ) ; 
 int blkid_probe_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ blkid_probe_is_wholedisk (int /*<<< orphan*/ ) ; 
 scalar_t__ blkid_probe_lookup_value (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkid_probe_set_partitions_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int probe_superblocks(blkid_probe pr) {
        struct stat st;
        int rc;

        /* TODO: Return negative errno. */

        if (fstat(blkid_probe_get_fd(pr), &st))
                return -errno;

        blkid_probe_enable_partitions(pr, 1);

        if (!S_ISCHR(st.st_mode) &&
            blkid_probe_get_size(pr) <= 1024 * 1440 &&
            blkid_probe_is_wholedisk(pr)) {
                /*
                 * check if the small disk is partitioned, if yes then
                 * don't probe for filesystems.
                 */
                blkid_probe_enable_superblocks(pr, 0);

                rc = blkid_do_fullprobe(pr);
                if (rc < 0)
                        return rc;        /* -1 = error, 1 = nothing, 0 = success */

                if (blkid_probe_lookup_value(pr, "PTTYPE", NULL, NULL) == 0)
                        return 0;        /* partition table detected */
        }

        blkid_probe_set_partitions_flags(pr, BLKID_PARTS_ENTRY_DETAILS);
        blkid_probe_enable_superblocks(pr, 1);

        return blkid_do_safeprobe(pr);
}