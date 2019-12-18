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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* ToWide (char*) ; 
 scalar_t__ WriteConsoleW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int) ; 
 scalar_t__ _isatty (int) ; 
 int fputws (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (char*) ; 

int utf8_vfprintf( FILE *stream, const char *fmt, va_list ap )
{
#ifndef _WIN32
    return vfprintf (stream, fmt, ap);
#else
    char *str;
    int res = vasprintf (&str, fmt, ap);
    if (unlikely(res == -1))
        return -1;

#if !VLC_WINSTORE_APP
    /* Writing to the console is a lot of fun on Microsoft Windows.
     * If you use the standard I/O functions, you must use the OEM code page,
     * which is different from the usual ANSI code page. Or maybe not, if the
     * user called "chcp". Anyway, we prefer Unicode. */
    int fd = _fileno (stream);
    if (likely(fd != -1) && _isatty (fd))
    {
        wchar_t *wide = ToWide (str);
        if (likely(wide != NULL))
        {
            HANDLE h = (HANDLE)((uintptr_t)_get_osfhandle (fd));
            DWORD out;
            /* XXX: It is not clear whether WriteConsole() wants the number of
             * Unicode characters or the size of the wchar_t array. */
            BOOL ok = WriteConsoleW (h, wide, wcslen (wide), &out, NULL);
            free (wide);
            if (ok)
                goto out;
        }
    }
#endif
    wchar_t *wide = ToWide(str);
    if (likely(wide != NULL))
    {
        res = fputws(wide, stream);
        free(wide);
    }
    else
        res = -1;
out:
    free (str);
    return res;
#endif
}