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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int mkdir (char const*,int /*<<< orphan*/ ) ; 

int
seaf_util_mkdir (const char *path, mode_t mode)
{
#ifdef WIN32
    wchar_t *wpath = win32_long_path (path);
    int ret = 0;

    if (!CreateDirectoryW (wpath, NULL)) {
        ret = -1;
        errno = windows_error_to_errno (GetLastError());
    }

    g_free (wpath);
    return ret;
#else
    return mkdir (path, mode);
#endif
}