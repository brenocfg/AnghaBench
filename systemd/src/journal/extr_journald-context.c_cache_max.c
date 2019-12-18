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

/* Variables and functions */
 size_t CACHE_MAX_FALLBACK ; 
 int /*<<< orphan*/  CACHE_MAX_MAX ; 
 int /*<<< orphan*/  CACHE_MAX_MIN ; 
 size_t CLAMP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int procfs_memory_get (int*,int /*<<< orphan*/ *) ; 
 int sc_arg_max () ; 

__attribute__((used)) static size_t cache_max(void) {
        static size_t cached = -1;

        if (cached == (size_t) -1) {
                uint64_t mem_total;
                int r;

                r = procfs_memory_get(&mem_total, NULL);
                if (r < 0) {
                        log_warning_errno(r, "Cannot query /proc/meminfo for MemTotal: %m");
                        cached = CACHE_MAX_FALLBACK;
                } else
                        /* Cache entries are usually a few kB, but the process cmdline is controlled by the
                         * user and can be up to _SC_ARG_MAX, usually 2MB. Let's say that approximately up to
                         * 1/8th of memory may be used by the cache.
                         *
                         * In the common case, this formula gives 64 cache entries for each GB of RAM.
                         */
                        cached = CLAMP(mem_total / 8 / sc_arg_max(), CACHE_MAX_MIN, CACHE_MAX_MAX);
        }

        return cached;
}