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
 int /*<<< orphan*/  free (char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  print_zpool_dir_scripts (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strtok (char*,char*) ; 
 char* zpool_get_cmd_search_path () ; 

__attribute__((used)) static void
print_zpool_script_list(char *subcommand)
{
	char *dir, *sp;

	printf(gettext("Available 'zpool %s -c' commands:\n"), subcommand);

	sp = zpool_get_cmd_search_path();
	if (sp == NULL)
		return;

	dir = strtok(sp, ":");
	while (dir != NULL) {
		print_zpool_dir_scripts(dir);
		dir = strtok(NULL, ":");
	}

	free(sp);
}