#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_6__ {scalar_t__ box_idx; scalar_t__ box_height; scalar_t__ box_type; int plidx_follow; int /*<<< orphan*/  box_lines_total; int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 scalar_t__ BOX_PLAYLIST ; 
 int /*<<< orphan*/  CheckIdx (TYPE_2__*) ; 
#define  KEY_DOWN 134 
#define  KEY_END 133 
#define  KEY_HOME 132 
#define  KEY_NPAGE 131 
#define  KEY_PPAGE 130 
#define  KEY_SELECT 129 
#define  KEY_UP 128 
 scalar_t__ vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool HandleListKey(intf_thread_t *intf, int key)
{
    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;

    switch(key)
    {
#ifdef __FreeBSD__
/* workaround for FreeBSD + xterm:
 * see http://www.nabble.com/curses-vs.-xterm-key-mismatch-t3574377.html */
    case KEY_SELECT:
#endif
    case KEY_END:  sys->box_idx = sys->box_lines_total - 1; break;
    case KEY_HOME: sys->box_idx = 0;                            break;
    case KEY_UP:   sys->box_idx--;                              break;
    case KEY_DOWN: sys->box_idx++;                              break;
    case KEY_PPAGE:sys->box_idx -= sys->box_height;         break;
    case KEY_NPAGE:sys->box_idx += sys->box_height;         break;
    default:
        return false;
    }

    CheckIdx(sys);

    if (sys->box_type == BOX_PLAYLIST) {
        vlc_playlist_Lock(playlist);
        sys->plidx_follow =
            sys->box_idx == vlc_playlist_GetCurrentIndex(playlist);
        vlc_playlist_Unlock(playlist);
    }

    return true;
}