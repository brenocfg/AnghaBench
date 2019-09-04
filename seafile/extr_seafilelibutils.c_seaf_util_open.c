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
 int open (char const*,int) ; 

int
seaf_util_open (const char *path, int flags)
{
#ifdef WIN32
    wchar_t *wpath;
    DWORD access = 0;
    HANDLE handle;
    int fd;

    access |= GENERIC_READ;
    if (flags & (O_WRONLY | O_RDWR))
        access |= GENERIC_WRITE;

    wpath = win32_long_path (path);

    handle = CreateFileW (wpath,
                          access,
                          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                          NULL,
                          OPEN_EXISTING,
                          0,
                          NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        errno = windows_error_to_errno (GetLastError());
        g_free (wpath);
        return -1;
    }

    fd = _open_osfhandle ((intptr_t)handle, 0);

    g_free (wpath);
    return fd;
#else
    return open (path, flags);
#endif
}