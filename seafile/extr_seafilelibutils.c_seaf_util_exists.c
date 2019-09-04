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
typedef  int gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 

gboolean
seaf_util_exists (const char *path)
{
#ifdef WIN32
    wchar_t *wpath = win32_long_path (path);
    DWORD attrs;
    gboolean ret;

    attrs = GetFileAttributesW (wpath);
    ret = (attrs != INVALID_FILE_ATTRIBUTES);

    g_free (wpath);
    return ret;
#else
    return (access (path, F_OK) == 0);
#endif
}