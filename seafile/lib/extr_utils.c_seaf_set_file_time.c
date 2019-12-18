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
typedef  scalar_t__ time_t ;
struct utimbuf {scalar_t__ modtime; int /*<<< orphan*/  actime; } ;
struct stat {int /*<<< orphan*/  st_atime; } ;
typedef  scalar_t__ guint64 ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_utc_file_time (char const*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int utime (char const*,struct utimbuf*) ; 
 int /*<<< orphan*/ * win32_long_path (char const*) ; 

int
seaf_set_file_time (const char *path, guint64 mtime)
{
#ifndef WIN32
    struct stat st;
    struct utimbuf times;

    if (stat (path, &st) < 0) {
        g_warning ("Failed to stat %s: %s.\n", path, strerror(errno));
        return -1;
    }

    times.actime = st.st_atime;
    times.modtime = (time_t)mtime;

    return utime (path, &times);
#else
    wchar_t *wpath = win32_long_path (path);
    int ret = 0;

    if (set_utc_file_time (path, wpath, mtime) < 0)
        ret = -1;

    g_free (wpath);
    return ret;
#endif
}