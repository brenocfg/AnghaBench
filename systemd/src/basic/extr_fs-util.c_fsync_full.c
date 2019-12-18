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
 int errno ; 
 scalar_t__ fsync (int) ; 
 int fsync_directory_of_file (int) ; 

int fsync_full(int fd) {
        int r, q;

        /* Sync both the file and the directory */

        r = fsync(fd) < 0 ? -errno : 0;
        q = fsync_directory_of_file(fd);

        return r < 0 ? r : q;
}