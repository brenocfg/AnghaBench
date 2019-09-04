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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* KEYMAP_PATH ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 char* pathjoin (char*,char const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

FILE *
xkeymap_open(const char *filename)
{
	char *path1, *path2;
	char *home;
	FILE *fp;

	/* Try ~/.rdesktop/keymaps */
	home = getenv("HOME");
	if (home)
	{
		path1 = pathjoin(home, ".rdesktop/keymaps");
		path2 = pathjoin(path1, filename);
		xfree(path1);
		fp = fopen(path2, "r");
		xfree(path2);
		if (fp)
			return fp;
	}

	/* Try KEYMAP_PATH */
	path1 = pathjoin(KEYMAP_PATH, filename);
	fp = fopen(path1, "r");
	xfree(path1);
	if (fp)
		return fp;

	/* Try current directory, in case we are running from the source
	   tree */
	path1 = pathjoin("keymaps", filename);
	fp = fopen(path1, "r");
	xfree(path1);
	if (fp)
		return fp;

	return NULL;
}