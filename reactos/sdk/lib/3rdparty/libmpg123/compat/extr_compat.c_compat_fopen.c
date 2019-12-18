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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * u2wlongpath (char const*) ; 
 int win32_utf8_wide (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

FILE* compat_fopen(const char *filename, const char *mode)
{
	FILE* stream = NULL;
#ifdef WANT_WIN32_UNICODE
	int cnt = 0;
	wchar_t *wname = NULL;
	wchar_t *wmode = NULL;

	wname = u2wlongpath(filename);
	if(!wname)
		goto fopen_fallback;
	cnt = win32_utf8_wide(mode, &wmode, NULL);
	if( (wmode == NULL) || (cnt == 0))
		goto fopen_fallback;

	stream = _wfopen(wname, wmode);
	if(stream) goto fopen_ok;

fopen_fallback:
#endif
	stream = fopen(filename, mode);
#ifdef WANT_WIN32_UNICODE

fopen_ok:
	free(wmode);
	free(wname);
#endif
	return stream;
}