#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int __int64 ;
struct TYPE_7__ {int dwFileAttributes; scalar_t__ nFileSizeLow; scalar_t__ nFileSizeHigh; int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  ftCreationTime; int /*<<< orphan*/  ftLastAccessTime; } ;
typedef  TYPE_1__ WIN32_FILE_ATTRIBUTE_DATA ;
struct TYPE_8__ {int st_mode; scalar_t__ st_size; void* st_mtime; void* st_ctime; void* st_atime; } ;
typedef  TYPE_2__ SeafStat ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  GetFileAttributesExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetFileExInfoStandard ; 
 int /*<<< orphan*/  GetLastError () ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int S_IRWXU ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  errno ; 
 void* file_time_to_unix_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int stat (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/ * win32_long_path (char const*) ; 
 int /*<<< orphan*/  windows_error_to_errno (int /*<<< orphan*/ ) ; 

int
seaf_stat (const char *path, SeafStat *st)
{
#ifdef WIN32
    wchar_t *wpath = win32_long_path (path);
    WIN32_FILE_ATTRIBUTE_DATA attrs;
    int ret = 0;

    if (!GetFileAttributesExW (wpath, GetFileExInfoStandard, &attrs)) {
        ret = -1;
        errno = windows_error_to_errno (GetLastError());
        goto out;
    }

    memset (st, 0, sizeof(SeafStat));

    if (attrs.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        st->st_mode = (S_IFDIR | S_IRWXU);
    else
        st->st_mode = (S_IFREG | S_IRUSR | S_IWUSR);

    st->st_atime = file_time_to_unix_time (&attrs.ftLastAccessTime);
    st->st_ctime = file_time_to_unix_time (&attrs.ftCreationTime);
    st->st_mtime = file_time_to_unix_time (&attrs.ftLastWriteTime);

    st->st_size = ((((__int64)attrs.nFileSizeHigh)<<32) + attrs.nFileSizeLow);

out:
    g_free (wpath);

    return ret;
#else
    return stat (path, st);
#endif
}