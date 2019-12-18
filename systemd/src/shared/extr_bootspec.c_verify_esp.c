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
typedef  scalar_t__ uint32_t ;
struct statfs {int /*<<< orphan*/  f_type; } ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_TYPE_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MSDOS_SUPER_MAGIC ; 
 int /*<<< orphan*/  SD_ID128_NULL ; 
 scalar_t__ SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ detect_container () ; 
 scalar_t__ errno ; 
 scalar_t__ getenv_bool (char*) ; 
 int log_full_errno (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 scalar_t__ statfs (char const*,struct statfs*) ; 
 int verify_esp_blkid (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int verify_esp_udev (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int verify_fsroot_dir (char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int verify_esp(
                const char *p,
                bool searching,
                bool unprivileged_mode,
                uint32_t *ret_part,
                uint64_t *ret_pstart,
                uint64_t *ret_psize,
                sd_id128_t *ret_uuid) {

        bool relax_checks;
        dev_t devid;
        int r;

        assert(p);

        /* This logs about all errors, except:
         *
         *  -ENOENT        → if 'searching' is set, and the dir doesn't exist
         *  -EADDRNOTAVAIL → if 'searching' is set, and the dir doesn't look like an ESP
         *  -EACESS        → if 'unprivileged_mode' is set, and we have trouble accessing the thing
         */

        relax_checks = getenv_bool("SYSTEMD_RELAX_ESP_CHECKS") > 0;

        /* Non-root user can only check the status, so if an error occurred in the following, it does not cause any
         * issues. Let's also, silence the error messages. */

        if (!relax_checks) {
                struct statfs sfs;

                if (statfs(p, &sfs) < 0)
                        /* If we are searching for the mount point, don't generate a log message if we can't find the path */
                        return log_full_errno((searching && errno == ENOENT) ||
                                              (unprivileged_mode && errno == EACCES) ? LOG_DEBUG : LOG_ERR, errno,
                                              "Failed to check file system type of \"%s\": %m", p);

                if (!F_TYPE_EQUAL(sfs.f_type, MSDOS_SUPER_MAGIC))
                        return log_full_errno(searching ? LOG_DEBUG : LOG_ERR,
                                              SYNTHETIC_ERRNO(searching ? EADDRNOTAVAIL : ENODEV),
                                              "File system \"%s\" is not a FAT EFI System Partition (ESP) file system.", p);
        }

        r = verify_fsroot_dir(p, searching, unprivileged_mode, &devid);
        if (r < 0)
                return r;

        /* In a container we don't have access to block devices, skip this part of the verification, we trust
         * the container manager set everything up correctly on its own. */
        if (detect_container() > 0 || relax_checks)
                goto finish;

        /* If we are unprivileged we ask udev for the metadata about the partition. If we are privileged we
         * use blkid instead. Why? Because this code is called from 'bootctl' which is pretty much an
         * emergency recovery tool that should also work when udev isn't up (i.e. from the emergency shell),
         * however blkid can't work if we have no privileges to access block devices directly, which is why
         * we use udev in that case. */
        if (unprivileged_mode)
                return verify_esp_udev(devid, searching, ret_part, ret_pstart, ret_psize, ret_uuid);
        else
                return verify_esp_blkid(devid, searching, ret_part, ret_pstart, ret_psize, ret_uuid);

finish:
        if (ret_part)
                *ret_part = 0;
        if (ret_pstart)
                *ret_pstart = 0;
        if (ret_psize)
                *ret_psize = 0;
        if (ret_uuid)
                *ret_uuid = SD_ID128_NULL;

        return 0;
}