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

/* Variables and functions */
 int BTRFS_SNAPSHOT_FALLBACK_COPY ; 
 int BTRFS_SNAPSHOT_FALLBACK_DIRECTORY ; 
 int BTRFS_SNAPSHOT_QUOTA ; 
 int BTRFS_SNAPSHOT_RECURSIVE ; 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int REMOVE_SUBVOLUME ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int btrfs_subvol_snapshot (char const*,char const*,int) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 char* prefix_roota (char const*,char const*) ; 
 int /*<<< orphan*/  rm_rf (char const*,int) ; 

int pull_make_local_copy(const char *final, const char *image_root, const char *local, bool force_local) {
        const char *p;
        int r;

        assert(final);
        assert(local);

        if (!image_root)
                image_root = "/var/lib/machines";

        p = prefix_roota(image_root, local);

        if (force_local)
                (void) rm_rf(p, REMOVE_ROOT|REMOVE_PHYSICAL|REMOVE_SUBVOLUME);

        r = btrfs_subvol_snapshot(final, p,
                                  BTRFS_SNAPSHOT_QUOTA|
                                  BTRFS_SNAPSHOT_FALLBACK_COPY|
                                  BTRFS_SNAPSHOT_FALLBACK_DIRECTORY|
                                  BTRFS_SNAPSHOT_RECURSIVE);
        if (r < 0)
                return log_error_errno(r, "Failed to create local image: %m");

        log_info("Created new local image '%s'.", local);

        return 0;
}