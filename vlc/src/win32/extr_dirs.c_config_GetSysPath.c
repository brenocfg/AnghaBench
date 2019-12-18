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
typedef  int vlc_sysdir_t ;

/* Variables and functions */
#define  VLC_LOCALE_DIR 132 
#define  VLC_PKG_DATA_DIR 131 
#define  VLC_PKG_LIBEXEC_DIR 130 
#define  VLC_PKG_LIB_DIR 129 
#define  VLC_SYSDATA_DIR 128 
 int asprintf (char**,char*,char*,char const*) ; 
 char* config_GetDataDir () ; 
 char* config_GetLibDir () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

char *config_GetSysPath(vlc_sysdir_t type, const char *filename)
{
    char *dir = NULL;

    switch (type)
    {
        case VLC_PKG_DATA_DIR:
            dir = config_GetDataDir();
            break;
        case VLC_PKG_LIB_DIR:
        case VLC_PKG_LIBEXEC_DIR:
            dir = config_GetLibDir();
            break;
        case VLC_SYSDATA_DIR:
            break;
        case VLC_LOCALE_DIR:
            dir = config_GetSysPath(VLC_PKG_DATA_DIR, "locale");
            break;
        default:
            vlc_assert_unreachable();
    }

    if (filename == NULL || unlikely(dir == NULL))
        return dir;

    char *path;
    if (unlikely(asprintf(&path, "%s/%s", dir, filename) == -1))
        path = NULL;
    free(dir);
    return path;
}