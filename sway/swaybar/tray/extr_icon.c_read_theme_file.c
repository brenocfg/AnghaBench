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
struct icon_theme {void* dir; int /*<<< orphan*/  subdirs; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct icon_theme* calloc (int,int) ; 
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  destroy_theme (struct icon_theme*) ; 
 int entry_handler (char*,char*,char*,struct icon_theme*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int group_handler (char*,char*,struct icon_theme*) ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/  iscntrl (char) ; 
 scalar_t__ isspace (char) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 void* strdup (char*) ; 
 scalar_t__ validate_icon_theme (struct icon_theme*) ; 

__attribute__((used)) static struct icon_theme *read_theme_file(char *basedir, char *theme_name) {
	// look for index.theme file
	size_t path_len = snprintf(NULL, 0, "%s/%s/index.theme", basedir,
			theme_name) + 1;
	char *path = malloc(path_len);
	if (!path) {
		return NULL;
	}
	snprintf(path, path_len, "%s/%s/index.theme", basedir, theme_name);
	FILE *theme_file = fopen(path, "r");
	free(path);
	if (!theme_file) {
		return NULL;
	}

	struct icon_theme *theme = calloc(1, sizeof(struct icon_theme));
	if (!theme) {
		fclose(theme_file);
		return NULL;
	}
	theme->subdirs = create_list();

	bool error = false;
	char *group = NULL;
	char *full_line = NULL;
	size_t full_len = 0;
	ssize_t nread;
	while ((nread = getline(&full_line, &full_len, theme_file)) != -1) {
		char *line = full_line - 1;
		while (isspace(*++line)) {} // remove leading whitespace
		if (!*line || line[0] == '#') continue; // ignore blank lines & comments

		int len = nread - (line - full_line);
		while (isspace(line[--len])) {}
		line[++len] = '\0'; // remove trailing whitespace

		if (line[0] == '[') { // group header
			// check well-formed
			if (line[--len] != ']') {
				error = true;
				break;
			}
			int i = 1;
			for (; !iscntrl(line[i]) && line[i] != '[' && line[i] != ']'; ++i) {}
			if (i < len) {
				error = true;
				break;
			}

			// call handler
			line[len] = '\0';
			error = group_handler(group, &line[1], theme);
			if (error) {
				break;
			}
			free(group);
			group = strdup(&line[1]);
		} else { // key-value pair
			if (!group) {
				error = true;
				break;
			}
			// check well-formed
			int eok = 0;
			for (; isalnum(line[eok]) || line[eok] == '-'; ++eok) {} // TODO locale?
			int i = eok - 1;
			while (isspace(line[++i])) {}
			if (line[i] != '=') {
				error = true;
				break;
			}

			line[eok] = '\0'; // split into key-value pair
			char *value = &line[i];
			while (isspace(*++value)) {}
			// TODO unescape value
			error = entry_handler(group, line, value, theme);
			if (error) {
				break;
			}
		}
	}

	if (!error && group) {
		error = group_handler(group, NULL, theme);
	}

	free(group);
	free(full_line);
	fclose(theme_file);

	if (!error && validate_icon_theme(theme)) {
		theme->dir = strdup(theme_name);
		return theme;
	} else {
		destroy_theme(theme);
		return NULL;
	}
}