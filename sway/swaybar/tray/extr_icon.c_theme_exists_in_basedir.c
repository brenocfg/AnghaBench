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
 int dir_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 

__attribute__((used)) static bool theme_exists_in_basedir(char *theme, char *basedir) {
	size_t path_len = snprintf(NULL, 0, "%s/%s", basedir, theme) + 1;
	char *path = malloc(path_len);
	snprintf(path, path_len, "%s/%s", basedir, theme);
	bool ret = dir_exists(path);
	free(path);
	return ret;
}