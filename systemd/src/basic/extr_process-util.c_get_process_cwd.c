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
 int /*<<< orphan*/  assert (int) ; 
 int get_process_link_contents (char const*,char**) ; 
 char* procfs_file_alloca (scalar_t__,char*) ; 

int get_process_cwd(pid_t pid, char **cwd) {
        const char *p;

        assert(pid >= 0);

        p = procfs_file_alloca(pid, "cwd");

        return get_process_link_contents(p, cwd);
}