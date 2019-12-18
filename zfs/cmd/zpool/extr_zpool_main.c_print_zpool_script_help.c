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
 int /*<<< orphan*/  is_blank_str (char*) ; 
 int /*<<< orphan*/  libzfs_free_str_array (char**,int) ; 
 int libzfs_run_process_get_stdout_nopath (char*,char**,int /*<<< orphan*/ *,char***,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
print_zpool_script_help(char *name, char *path)
{
	char *argv[] = {path, "-h", NULL};
	char **lines = NULL;
	int lines_cnt = 0;
	int rc;

	rc = libzfs_run_process_get_stdout_nopath(path, argv, NULL, &lines,
	    &lines_cnt);
	if (rc != 0 || lines == NULL || lines_cnt <= 0) {
		if (lines != NULL)
			libzfs_free_str_array(lines, lines_cnt);
		return;
	}

	for (int i = 0; i < lines_cnt; i++)
		if (!is_blank_str(lines[i]))
			printf("  %-14s  %s\n", name, lines[i]);

	libzfs_free_str_array(lines, lines_cnt);
}