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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errno ; 
 int fflush_and_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fsync (int /*<<< orphan*/ ) ; 
 int fsync_directory_of_file (int /*<<< orphan*/ ) ; 

int fflush_sync_and_check(FILE *f) {
        int r;

        assert(f);

        r = fflush_and_check(f);
        if (r < 0)
                return r;

        if (fsync(fileno(f)) < 0)
                return -errno;

        r = fsync_directory_of_file(fileno(f));
        if (r < 0)
                return r;

        return 0;
}