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
typedef  int /*<<< orphan*/  extensions ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int snprintf (char*,size_t,char*,char*,char*,char*,char*,...) ; 

__attribute__((used)) static char *find_icon_in_subdir(char *name, char *basedir, char *theme,
		char *subdir) {
	static const char *extensions[] = {
#if HAVE_GDK_PIXBUF
		"svg",
#endif
		"png",
#if HAVE_GDK_PIXBUF
		"xpm"
#endif
	};

	size_t path_len = snprintf(NULL, 0, "%s/%s/%s/%s.EXT", basedir, theme,
			subdir, name) + 1;
	char *path = malloc(path_len);

	for (size_t i = 0; i < sizeof(extensions) / sizeof(*extensions); ++i) {
		snprintf(path, path_len, "%s/%s/%s/%s.%s", basedir, theme, subdir,
				name, extensions[i]);
		if (access(path, R_OK) == 0) {
			return path;
		}
	}

	free(path);
	return NULL;
}