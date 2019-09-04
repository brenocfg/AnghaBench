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
typedef  int /*<<< orphan*/  SeafStat ;

/* Variables and functions */
 int stat (char const*,int /*<<< orphan*/ *) ; 

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