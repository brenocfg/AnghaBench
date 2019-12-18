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
struct stat {scalar_t__ st_ino; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int errno ; 
 int get_mount_namespace_leader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_process_cmdline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* procfs_file_alloca (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int get_process_container_parent_cmdline(pid_t pid, char** cmdline) {
        int r = 0;
        pid_t container_pid;
        const char *proc_root_path;
        struct stat root_stat, proc_root_stat;

        /* To compare inodes of / and /proc/[pid]/root */
        if (stat("/", &root_stat) < 0)
                return -errno;

        proc_root_path = procfs_file_alloca(pid, "root");
        if (stat(proc_root_path, &proc_root_stat) < 0)
                return -errno;

        /* The process uses system root. */
        if (proc_root_stat.st_ino == root_stat.st_ino) {
                *cmdline = NULL;
                return 0;
        }

        r = get_mount_namespace_leader(pid, &container_pid);
        if (r < 0)
                return r;

        r = get_process_cmdline(container_pid, SIZE_MAX, 0, cmdline);
        if (r < 0)
                return r;

        return 1;
}