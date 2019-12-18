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
typedef  int /*<<< orphan*/  mode_t ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * win32_long_path (char const*) ; 
 int /*<<< orphan*/  windows_error_to_errno (int /*<<< orphan*/ ) ; 

int
seaf_util_create (const char *path, int flags, mode_t mode)
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
                          CREATE_ALWAYS,
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
    return open (path, flags, mode);
#endif
}