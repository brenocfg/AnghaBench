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

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

int compat_isdir(const char *path)
{
	int ret = 0;
#ifdef WANT_WIN32_UNICODE
	wchar_t *wpath;
	wpath = u2wlongpath(path);
	if(wpath)
	{
		DWORD attr = GetFileAttributesW(wpath);
		if(attr != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_DIRECTORY)
			ret=1;
		free(wpath);
	}
#else
	struct stat sb;
	if(path && !stat(path, &sb))
	{
		if(S_ISDIR(sb.st_mode))
			ret=1;
	}
#endif
	return ret;
}