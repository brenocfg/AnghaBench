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
struct icon_theme {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_list () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct icon_theme*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct icon_theme* read_theme_file (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static list_t *load_themes_in_dir(char *basedir) {
	DIR *dir;
	if (!(dir = opendir(basedir))) {
		return NULL;
	}

	list_t *themes = create_list();
	struct dirent *entry;
	while ((entry = readdir(dir))) {
		if (entry->d_name[0] == '.') continue;

		struct icon_theme *theme = read_theme_file(basedir, entry->d_name);
		if (theme) {
			list_add(themes, theme);
		}
	}
	closedir(dir);
	return themes;
}