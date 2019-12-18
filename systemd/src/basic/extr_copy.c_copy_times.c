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
typedef  int /*<<< orphan*/  usec_t ;
struct timespec {int dummy; } ;
struct stat {struct timespec st_mtim; struct timespec st_atim; } ;
typedef  int /*<<< orphan*/  CopyFlags ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_CRTIME ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fd_getcrtime (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_setcrtime (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ futimens (int,struct timespec*) ; 

int copy_times(int fdf, int fdt, CopyFlags flags) {
        struct timespec ut[2];
        struct stat st;

        assert(fdf >= 0);
        assert(fdt >= 0);

        if (fstat(fdf, &st) < 0)
                return -errno;

        ut[0] = st.st_atim;
        ut[1] = st.st_mtim;

        if (futimens(fdt, ut) < 0)
                return -errno;

        if (FLAGS_SET(flags, COPY_CRTIME)) {
                usec_t crtime;

                if (fd_getcrtime(fdf, &crtime) >= 0)
                        (void) fd_setcrtime(fdt, crtime);
        }

        return 0;
}