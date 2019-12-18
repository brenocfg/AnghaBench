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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _wgetenv (int /*<<< orphan*/ *) ; 
 char* compat_strdup (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* getenv (char const*) ; 
 scalar_t__ win32_utf8_wide (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win32_wide_utf8 (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 

char *compat_getenv(const char* name)
{
	char *ret = NULL;
#ifdef WANT_WIN32_UNICODE
	wchar_t *env;
	wchar_t *wname = NULL;
	if(win32_utf8_wide(name, &wname, NULL) > 0)
	{
		env = _wgetenv(wname);
		free(wname);
		if(env)
			win32_wide_utf8(env, &ret, NULL);
	}
#else
	ret = getenv(name);
	if(ret)
		ret = compat_strdup(ret);
#endif
	return ret;
}