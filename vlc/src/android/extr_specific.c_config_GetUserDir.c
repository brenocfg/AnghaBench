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
 int /*<<< orphan*/  assert (int) ; 
 char* config_GetGenericDir (char const*) ; 
 char* config_GetHomeDir (char*,char*) ; 
 char** ppsz_generic_names ; 

char *config_GetUserDir (vlc_userdir_t type)
{
    switch (type)
    {
        case VLC_USERDATA_DIR:
            return config_GetHomeDir(".share",
                "/sdcard/Android/data/org.videolan.vlc");
        case VLC_CACHE_DIR:
            return config_GetHomeDir(".cache",
                "/sdcard/Android/data/org.videolan.vlc/cache");
        case VLC_HOME_DIR:
            return config_GetHomeDir(NULL, NULL);
        case VLC_CONFIG_DIR:
            return config_GetHomeDir(".config", NULL);

        case VLC_DESKTOP_DIR:
        case VLC_DOWNLOAD_DIR:
        case VLC_TEMPLATES_DIR:
        case VLC_PUBLICSHARE_DIR:
        case VLC_DOCUMENTS_DIR:
        case VLC_MUSIC_DIR:
        case VLC_PICTURES_DIR:
        case VLC_VIDEOS_DIR:
        {
            assert(type >= VLC_DESKTOP_DIR && type <= VLC_VIDEOS_DIR);
            const char *psz_name = ppsz_generic_names[type - VLC_DESKTOP_DIR];
            if (psz_name != NULL)
                return config_GetGenericDir(psz_name);
        }
    }
    return NULL;
}