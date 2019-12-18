#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct TYPE_10__ {int length; int /*<<< orphan*/ * items; } ;
typedef  TYPE_2__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRDE_UNDEF ; 
 TYPE_2__* create_list () ; 
 scalar_t__ dir_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  list_add (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (TYPE_2__*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 char* strdup (char*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ wordexp (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

__attribute__((used)) static list_t *get_basedirs(void) {
	list_t *basedirs = create_list();
	list_add(basedirs, strdup("$HOME/.icons")); // deprecated

	char *data_home = getenv("XDG_DATA_HOME");
	list_add(basedirs, strdup(data_home && *data_home ?
			"$XDG_DATA_HOME/icons" : "$HOME/.local/share/icons"));

	list_add(basedirs, strdup("/usr/share/pixmaps"));

	char *data_dirs = getenv("XDG_DATA_DIRS");
	if (!(data_dirs && *data_dirs)) {
		data_dirs = "/usr/local/share:/usr/share";
	}
	data_dirs = strdup(data_dirs);
	char *dir = strtok(data_dirs, ":");
	do {
		size_t path_len = snprintf(NULL, 0, "%s/icons", dir) + 1;
		char *path = malloc(path_len);
		snprintf(path, path_len, "%s/icons", dir);
		list_add(basedirs, path);
	} while ((dir = strtok(NULL, ":")));
	free(data_dirs);

	list_t *basedirs_expanded = create_list();
	for (int i = 0; i < basedirs->length; ++i) {
		wordexp_t p;
		if (wordexp(basedirs->items[i], &p, WRDE_UNDEF) == 0) {
			if (dir_exists(p.we_wordv[0])) {
				list_add(basedirs_expanded, strdup(p.we_wordv[0]));
			}
			wordfree(&p);
		}
	}

	list_free_items_and_destroy(basedirs);

	return basedirs_expanded;
}