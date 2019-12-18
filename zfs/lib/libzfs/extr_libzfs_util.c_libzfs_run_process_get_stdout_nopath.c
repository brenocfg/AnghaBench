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
 int /*<<< orphan*/  NO_DEFAULT_PATH ; 
 int libzfs_run_process_impl (char const*,char**,char**,int /*<<< orphan*/ ,char***,int*) ; 

int
libzfs_run_process_get_stdout_nopath(const char *path, char *argv[],
    char *env[], char **lines[], int *lines_cnt)
{
	return (libzfs_run_process_impl(path, argv, env, NO_DEFAULT_PATH,
	    lines, lines_cnt));
}