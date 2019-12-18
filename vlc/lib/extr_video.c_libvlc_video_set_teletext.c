#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int libvlc_teletext_key_blue ; 
 int libvlc_teletext_key_green ; 
 int libvlc_teletext_key_index ; 
 int libvlc_teletext_key_red ; 
 int libvlc_teletext_key_yellow ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectTeletextPage (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_SetTeletextEnabled (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

void libvlc_video_set_teletext( libvlc_media_player_t *p_mi, int i_page )
{
    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    if (i_page == 0)
        vlc_player_SetTeletextEnabled(player, false);
    else if (i_page > 0)
    {
        if (i_page >= 1000)
        {
            bool is_key = i_page == libvlc_teletext_key_red
                       || i_page == libvlc_teletext_key_green
                       || i_page == libvlc_teletext_key_yellow
                       || i_page == libvlc_teletext_key_blue
                       || i_page == libvlc_teletext_key_index;
            if (!is_key)
            {
                libvlc_printerr("Invalid key action");
                return;
            }
        }
        vlc_player_SetTeletextEnabled(player, true);
        vlc_player_SelectTeletextPage(player, i_page);
    }
    else
    {
        libvlc_printerr("Invalid page number");
        return;
    }

    vlc_player_Unlock(player);
}