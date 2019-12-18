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
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;
struct TYPE_3__ {scalar_t__ i_duration; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 scalar_t__ INPUT_DURATION_INDEFINITE ; 
 int MSTRTIME_MAX_SIZE ; 
 int /*<<< orphan*/  SEC_FROM_VLC_TICK (scalar_t__) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  msg_rc (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  secstotimestr (char*,int /*<<< orphan*/ ) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_playlist(intf_thread_t *p_intf, vlc_playlist_t *playlist)
{
    size_t count = vlc_playlist_Count(playlist);
    for (size_t i = 0; i < count; ++i)
    {
        vlc_playlist_item_t *plitem = vlc_playlist_Get(playlist, i);
        input_item_t *item = vlc_playlist_item_GetMedia(plitem);
        vlc_tick_t len = item->i_duration;
        if (len != INPUT_DURATION_INDEFINITE && len != VLC_TICK_INVALID)
        {
            char buf[MSTRTIME_MAX_SIZE];
            secstotimestr(buf, SEC_FROM_VLC_TICK(len));
            msg_rc("|-- %s (%s)", item->psz_name, buf);
        }
        else
            msg_rc("|-- %s", item->psz_name);
    }
}