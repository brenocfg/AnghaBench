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
typedef  int uint64_t ;
struct statvfs {int f_frsize; int f_blocks; int f_bfree; } ;

/* Variables and functions */
 int DEFAULT_KEEP_FREE ; 
 int DEFAULT_KEEP_FREE_UPPER ; 
 int DEFAULT_MAX_USE_LOWER ; 
 int DEFAULT_MAX_USE_UPPER ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fstatvfs (int,struct statvfs*) ; 

__attribute__((used)) static bool vacuum_necessary(int fd, uint64_t sum, uint64_t keep_free, uint64_t max_use) {
        uint64_t fs_size = 0, fs_free = (uint64_t) -1;
        struct statvfs sv;

        assert(fd >= 0);

        if (fstatvfs(fd, &sv) >= 0) {
                fs_size = sv.f_frsize * sv.f_blocks;
                fs_free = sv.f_frsize * sv.f_bfree;
        }

        if (max_use == (uint64_t) -1) {

                if (fs_size > 0) {
                        max_use = PAGE_ALIGN(fs_size / 10); /* 10% */

                        if (max_use > DEFAULT_MAX_USE_UPPER)
                                max_use = DEFAULT_MAX_USE_UPPER;

                        if (max_use < DEFAULT_MAX_USE_LOWER)
                                max_use = DEFAULT_MAX_USE_LOWER;
                } else
                        max_use = DEFAULT_MAX_USE_LOWER;
        } else
                max_use = PAGE_ALIGN(max_use);

        if (max_use > 0 && sum > max_use)
                return true;

        if (keep_free == (uint64_t) -1) {

                if (fs_size > 0) {
                        keep_free = PAGE_ALIGN((fs_size * 3) / 20); /* 15% */

                        if (keep_free > DEFAULT_KEEP_FREE_UPPER)
                                keep_free = DEFAULT_KEEP_FREE_UPPER;
                } else
                        keep_free = DEFAULT_KEEP_FREE;
        } else
                keep_free = PAGE_ALIGN(keep_free);

        if (keep_free > 0 && fs_free < keep_free)
                return true;

        return false;
}