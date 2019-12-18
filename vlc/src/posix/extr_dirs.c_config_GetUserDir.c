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
 char* config_GetAppDir (char*,char*) ; 
 char* config_GetHomeDir () ; 
 char* config_GetTypeDir (char*) ; 

char *config_GetUserDir (vlc_userdir_t type)
{
    switch (type)
    {
        case VLC_HOME_DIR:
            break;
        case VLC_CONFIG_DIR:
            return config_GetAppDir ("CONFIG", ".config");
        case VLC_USERDATA_DIR:
            return config_GetAppDir ("DATA", ".local/share");
        case VLC_CACHE_DIR:
            return config_GetAppDir ("CACHE", ".cache");

        case VLC_DESKTOP_DIR:
            return config_GetTypeDir ("DESKTOP");
        case VLC_DOWNLOAD_DIR:
            return config_GetTypeDir ("DOWNLOAD");
        case VLC_TEMPLATES_DIR:
            return config_GetTypeDir ("TEMPLATES");
        case VLC_PUBLICSHARE_DIR:
            return config_GetTypeDir ("PUBLICSHARE");
        case VLC_DOCUMENTS_DIR:
            return config_GetTypeDir ("DOCUMENTS");
        case VLC_MUSIC_DIR:
            return config_GetTypeDir ("MUSIC");
        case VLC_PICTURES_DIR:
            return config_GetTypeDir ("PICTURES");
        case VLC_VIDEOS_DIR:
            return config_GetTypeDir ("VIDEOS");
    }
    return config_GetHomeDir ();
}