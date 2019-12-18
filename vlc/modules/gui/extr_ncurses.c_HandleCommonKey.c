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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_8__ {int plidx_follow; char* open_chain; int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  BOX_BROWSE ; 
 int /*<<< orphan*/  BOX_HELP ; 
 int /*<<< orphan*/  BOX_INFO ; 
 int /*<<< orphan*/  BOX_LOG ; 
 int /*<<< orphan*/  BOX_META ; 
 int /*<<< orphan*/  BOX_OPEN ; 
 int /*<<< orphan*/  BOX_PLAYLIST ; 
 int /*<<< orphan*/  BOX_SEARCH ; 
 int /*<<< orphan*/  BOX_STATS ; 
 int /*<<< orphan*/  BoxSwitch (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChangePosition (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  Eject (TYPE_1__*,int /*<<< orphan*/ *) ; 
#define  KEY_CLEAR 131 
#define  KEY_EXIT 130 
#define  KEY_LEFT 129 
#define  KEY_RIGHT 128 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  getch () ; 
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectNextChapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectNextTitle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectNextTrack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_SelectPrevChapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectPrevTitle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_TogglePause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_aout_DecrementVolume (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_aout_IncrementVolume (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_aout_ToggleMute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_vout_ToggleFullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HandleCommonKey(intf_thread_t *intf, vlc_player_t *player, int key)
{
    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;

    switch(key)
    {
    case 0x1b:  /* ESC */
        /* See comment in HandleEditBoxKey() */
        if (getch() != ERR)
            return;
        /* Fall-through */

    case 'q':
    case 'Q':
    case KEY_EXIT:
        libvlc_Quit(vlc_object_instance(intf));
        return;

    case 'h':
    case 'H': BoxSwitch(sys, BOX_HELP);       return;
    case 'i': BoxSwitch(sys, BOX_INFO);       return;
    case 'M': BoxSwitch(sys, BOX_META);       return;
    case 'L': BoxSwitch(sys, BOX_LOG);        return;
    case 'P': BoxSwitch(sys, BOX_PLAYLIST);   return;
    case 'B': BoxSwitch(sys, BOX_BROWSE);     return;
    case 'S': BoxSwitch(sys, BOX_STATS);      return;

    case '/': /* Search */
        sys->plidx_follow = false;
        BoxSwitch(sys, BOX_SEARCH);
        return;

    case 'A': /* Open */
        sys->open_chain[0] = '\0';
        BoxSwitch(sys, BOX_OPEN);
        return;

    /* Navigation */
    case KEY_RIGHT: ChangePosition(player, +0.01); return;
    case KEY_LEFT:  ChangePosition(player, -0.01); return;

    /* Common control */
    case 'f':
        vlc_player_vout_ToggleFullscreen(player);
        return;

    case ' ':
        vlc_player_Lock(player);
        vlc_player_TogglePause(player);
        vlc_player_Unlock(player);
        return;
    case 's':
        vlc_player_Lock(player);
        vlc_player_Stop(player);
        vlc_player_Unlock(player);
        return;

    case 'e': Eject(intf, player);           return;

    case '[':
        vlc_player_Lock(player);
        vlc_player_SelectPrevTitle(player);
        vlc_player_Unlock(player);
        return;
    case ']':
        vlc_player_Lock(player);
        vlc_player_SelectNextTitle(player);
        vlc_player_Unlock(player);
        return;
    case '<':
        vlc_player_Lock(player);
        vlc_player_SelectPrevChapter(player);
        vlc_player_Unlock(player);
        return;
    case '>':
        vlc_player_Lock(player);
        vlc_player_SelectNextChapter(player);
        vlc_player_Unlock(player);
        return;

    case 'p':
        vlc_playlist_Lock(playlist);
        vlc_playlist_Prev(playlist);
        vlc_playlist_Unlock(playlist);
        break;
    case 'n':
        vlc_playlist_Lock(playlist);
        vlc_playlist_Next(playlist);
        vlc_playlist_Unlock(playlist);
        break;

    case 'a':
        vlc_player_Lock(player);
        vlc_player_aout_IncrementVolume(player, 1, NULL);
        vlc_player_Unlock(player);
        break;
    case 'z':
        vlc_player_Lock(player);
        vlc_player_aout_DecrementVolume(player, 1, NULL);
        vlc_player_Unlock(player);
        break;
    case 'm':
        vlc_player_Lock(player);
        vlc_player_aout_ToggleMute(player);
        vlc_player_Unlock(player);
        break;

    case 'c':
        vlc_player_Lock(player);
        vlc_player_SelectNextTrack(player, AUDIO_ES);
        vlc_player_Unlock(player);
        break;
    case 'v':
        vlc_player_Lock(player);
        vlc_player_SelectNextTrack(player, SPU_ES);
        vlc_player_Unlock(player);
        break;
    case 'b':
        vlc_player_Lock(player);
        vlc_player_SelectNextTrack(player, VIDEO_ES);
        vlc_player_Unlock(player);
        break;

    case 0x0c:  /* ^l */
    case KEY_CLEAR:
        break;

    default:
        return;
    }

    clear();
    return;
}