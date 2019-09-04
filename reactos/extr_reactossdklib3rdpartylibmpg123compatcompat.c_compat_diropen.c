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
struct compat_dir {int /*<<< orphan*/  path; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  compat_dirclose (struct compat_dir*) ; 
 int /*<<< orphan*/  compat_strdup (char*) ; 
 int /*<<< orphan*/  free (struct compat_dir*) ; 
 struct compat_dir* malloc (int) ; 
 int /*<<< orphan*/  opendir (char*) ; 

struct compat_dir* compat_diropen(char *path)
{
	struct compat_dir *cd;
	if(!path)
		return NULL;
	cd = malloc(sizeof(*cd));
	if(!cd)
		return NULL;
#ifdef WANT_WIN32_UNICODE
	cd->gotone = 0;
	{
		char *pattern;
		wchar_t *wpattern;
		pattern = compat_catpath(path, "*");
		wpattern = u2wlongpath(pattern);
		if(wpattern)
		{
			cd->ffn = FindFirstFileW(wpattern, &(cd->d));
			if(cd->ffn == INVALID_HANDLE_VALUE)
			{
				/* FindClose() only needed after successful first find, right? */
				free(cd);
				cd = NULL;
			}
			else
				cd->gotone = 1;
		}
		free(wpattern);
		free(pattern);
	}
#else
	cd->dir = opendir(path);
	if(!cd->dir)
	{
		free(cd);
		cd = NULL;
	}
#endif
	if(cd)
	{
		cd->path = compat_strdup(path);
		if(!cd->path)
		{
			compat_dirclose(cd);
			cd = NULL;
		}
	}
	return cd;
}