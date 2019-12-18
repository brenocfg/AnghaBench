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
#define  OSD_MUTE_ICON 131 
#define  OSD_PAUSE_ICON 130 
#define  OSD_PLAY_ICON 129 
#define  OSD_SPEAKER_ICON 128 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int vlc_osd_icon_from_string( const char *psz_name )
{
    static const struct
    {
        int i_icon;
        const char *psz_name;
    } pp_icons[] =
        { { OSD_PAUSE_ICON, "pause" },
          { OSD_PLAY_ICON, "play" },
          { OSD_SPEAKER_ICON, "speaker" },
          { OSD_MUTE_ICON, "mute" },
          { 0, NULL } };
    int i;
    for( i = 0; pp_icons[i].psz_name; i++ )
    {
        if( !strcmp( psz_name, pp_icons[i].psz_name ) )
            return pp_icons[i].i_icon;
    }
    return 0;
}