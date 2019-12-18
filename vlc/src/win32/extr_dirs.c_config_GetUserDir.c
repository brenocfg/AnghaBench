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
typedef  int vlc_userdir_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_LOCAL_APPDATA ; 
 int /*<<< orphan*/  CSIDL_MYMUSIC ; 
 int /*<<< orphan*/  CSIDL_MYPICTURES ; 
 int /*<<< orphan*/  CSIDL_MYVIDEO ; 
 int /*<<< orphan*/  CSIDL_PERSONAL ; 
#define  VLC_CACHE_DIR 139 
#define  VLC_CONFIG_DIR 138 
#define  VLC_DESKTOP_DIR 137 
#define  VLC_DOCUMENTS_DIR 136 
#define  VLC_DOWNLOAD_DIR 135 
#define  VLC_HOME_DIR 134 
#define  VLC_MUSIC_DIR 133 
#define  VLC_PICTURES_DIR 132 
#define  VLC_PUBLICSHARE_DIR 131 
#define  VLC_TEMPLATES_DIR 130 
#define  VLC_USERDATA_DIR 129 
#define  VLC_VIDEOS_DIR 128 
 char* config_GetAppDir () ; 
 char* config_GetShellDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

char *config_GetUserDir (vlc_userdir_t type)
{
    switch (type)
    {
        case VLC_HOME_DIR:
            return config_GetShellDir (CSIDL_PERSONAL);
        case VLC_CONFIG_DIR:
        case VLC_USERDATA_DIR:
            return config_GetAppDir ();
        case VLC_CACHE_DIR:
#if !VLC_WINSTORE_APP
            return config_GetAppDir ();
#else
            return config_GetShellDir (CSIDL_LOCAL_APPDATA);
#endif

        case VLC_DESKTOP_DIR:
        case VLC_DOWNLOAD_DIR:
        case VLC_TEMPLATES_DIR:
        case VLC_PUBLICSHARE_DIR:
        case VLC_DOCUMENTS_DIR:
            return config_GetUserDir(VLC_HOME_DIR);
        case VLC_MUSIC_DIR:
            return config_GetShellDir (CSIDL_MYMUSIC);
        case VLC_PICTURES_DIR:
            return config_GetShellDir (CSIDL_MYPICTURES);
        case VLC_VIDEOS_DIR:
            return config_GetShellDir (CSIDL_MYVIDEO);
    }
    vlc_assert_unreachable ();
}