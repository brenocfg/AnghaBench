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
struct stat {int st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXPATHLEN ; 
 scalar_t__ S_ISREG (int) ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  print_zpool_script_help (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static void
print_zpool_dir_scripts(char *dirpath)
{
	DIR *dir;
	struct dirent *ent;
	char fullpath[MAXPATHLEN];
	struct stat dir_stat;

	if ((dir = opendir(dirpath)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			sprintf(fullpath, "%s/%s", dirpath, ent->d_name);

			/* Print the scripts */
			if (stat(fullpath, &dir_stat) == 0)
				if (dir_stat.st_mode & S_IXUSR &&
				    S_ISREG(dir_stat.st_mode))
					print_zpool_script_help(ent->d_name,
					    fullpath);
		}
		closedir(dir);
	}
}