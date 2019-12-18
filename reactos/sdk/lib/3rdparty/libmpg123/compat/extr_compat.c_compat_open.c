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
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int _O_BINARY ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int _open (char const*,int,int) ; 
 int _wopen (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/ * u2wlongpath (char const*) ; 

int compat_open(const char *filename, int flags)
{
	int ret;
#if defined (WANT_WIN32_UNICODE)
	wchar_t *frag = NULL;

	frag = u2wlongpath(filename);
	/* Fallback to plain open when ucs-2 conversion fails */
	if(!frag)
		goto open_fallback;

	/*Try _wopen */
	ret = _wopen(frag, flags|_O_BINARY, _S_IREAD | _S_IWRITE);
	if(ret != -1 )
		goto open_ok; /* msdn says -1 means failure */

open_fallback:
#endif

#if (defined(WIN32) && !defined (__CYGWIN__))
	/* MSDN says POSIX function is deprecated beginning in Visual C++ 2005 */
	/* Try plain old _open(), if it fails, do nothing */
	ret = _open(filename, flags|_O_BINARY, _S_IREAD | _S_IWRITE);
#else
	ret = open(filename, flags, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
#endif

#if defined (WANT_WIN32_UNICODE)
open_ok:
	free(frag);
#endif

	return ret;
}