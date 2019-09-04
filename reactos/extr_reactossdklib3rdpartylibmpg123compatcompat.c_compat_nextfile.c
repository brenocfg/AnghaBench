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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct compat_dir {int /*<<< orphan*/  path; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 char* compat_catpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* compat_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

char* compat_nextfile(struct compat_dir *cd)
{
	if(!cd)
		return NULL;
#ifdef WANT_WIN32_UNICODE
	while(cd->gotone || FindNextFileW(cd->ffn, &(cd->d)))
	{
		cd->gotone = 0;
		if(!(cd->d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			char *ret;
			win32_wide_utf8(cd->d.cFileName, &ret, NULL);
			return ret;
		}
	}
#else
	{
		struct dirent *dp;
		while((dp = readdir(cd->dir)))
		{
			struct stat fst;
			char *fullpath = compat_catpath(cd->path, dp->d_name);
			if(fullpath && !stat(fullpath, &fst) && S_ISREG(fst.st_mode))
			{
				free(fullpath);
				return compat_strdup(dp->d_name);
			}
			free(fullpath);
		}
	}
#endif
	return NULL;
}