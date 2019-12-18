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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int files_same (char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getpid_cached () ; 
 char* procfs_file_alloca (scalar_t__,char*) ; 

int pid_from_same_root_fs(pid_t pid) {
        const char *root;

        if (pid < 0)
                return false;

        if (pid == 0 || pid == getpid_cached())
                return true;

        root = procfs_file_alloca(pid, "root");

        return files_same(root, "/proc/1/root", 0);
}