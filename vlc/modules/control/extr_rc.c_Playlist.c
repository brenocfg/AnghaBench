#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* psz_string; } ;
typedef  TYPE_2__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_9__ {TYPE_1__* p_sys; } ;
typedef  TYPE_3__ intf_thread_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;
typedef  enum vlc_playlist_playback_order { ____Placeholder_vlc_playlist_playback_order } vlc_playlist_playback_order ;
struct TYPE_7__ {int /*<<< orphan*/ * playlist; } ;

/* Variables and functions */
 int VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL ; 
 int VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int VLC_PLAYLIST_PLAYBACK_REPEAT_ALL ; 
 int VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT ; 
 int VLC_PLAYLIST_PLAYBACK_REPEAT_NONE ; 
 int VLC_SUCCESS ; 
 char* _ (char*) ; 
 long long atoll (scalar_t__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_print (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/ * parse_MRL (scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  vlc_ngettext (char*,char*,size_t) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackOrder (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackRepeat (int /*<<< orphan*/ *) ; 
 int vlc_playlist_InsertOne (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_PlayAt (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackOrder (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackRepeat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Playlist(intf_thread_t *intf, char const *psz_cmd,
                     vlc_value_t newval)
{
    vlc_playlist_t *playlist = intf->p_sys->playlist;

    vlc_playlist_Lock(playlist);

    /* Parse commands that require a playlist */
    if( !strcmp( psz_cmd, "repeat" ) )
    {
        bool b_update = true;
        enum vlc_playlist_playback_repeat repeat_mode =
            vlc_playlist_GetPlaybackRepeat(playlist);
        bool b_value = repeat_mode == VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT;

        if( strlen( newval.psz_string ) > 0 )
        {
            if ( ( !strncmp( newval.psz_string, "on", 2 )  &&  b_value ) ||
                 ( !strncmp( newval.psz_string, "off", 3 ) && !b_value ) )
            {
                b_update = false;
            }
        }

        if ( b_update )
        {
            b_value = !b_value;
            repeat_mode = b_value
                ? VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT
                : VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;
            vlc_playlist_SetPlaybackRepeat(playlist, repeat_mode);
        }
        msg_print(intf, "Setting repeat to %s", b_value ? "true" : "false");
    }
    else if( !strcmp( psz_cmd, "loop" ) )
    {
        bool b_update = true;
        enum vlc_playlist_playback_repeat repeat_mode =
            vlc_playlist_GetPlaybackRepeat(playlist);
        bool b_value = repeat_mode == VLC_PLAYLIST_PLAYBACK_REPEAT_ALL;

        if( strlen( newval.psz_string ) > 0 )
        {
            if ( ( !strncmp( newval.psz_string, "on", 2 )  &&  b_value ) ||
                 ( !strncmp( newval.psz_string, "off", 3 ) && !b_value ) )
            {
                b_update = false;
            }
        }

        if ( b_update )
        {
            b_value = !b_value;
            repeat_mode = b_value
                ? VLC_PLAYLIST_PLAYBACK_REPEAT_ALL
                : VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;
            vlc_playlist_SetPlaybackRepeat(playlist, repeat_mode);
        }
        msg_print(intf, "Setting loop to %s", b_value ? "true" : "false");
    }
    else if( !strcmp( psz_cmd, "random" ) )
    {
        bool b_update = true;
        enum vlc_playlist_playback_order order_mode =
            vlc_playlist_GetPlaybackOrder(playlist);
        bool b_value = order_mode == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM;

        if( strlen( newval.psz_string ) > 0 )
        {
            if ( ( !strncmp( newval.psz_string, "on", 2 )  &&  b_value ) ||
                 ( !strncmp( newval.psz_string, "off", 3 ) && !b_value ) )
            {
                b_update = false;
            }
        }

        if ( b_update )
        {
            b_value = !b_value;
            order_mode = b_value
                ? VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM
                : VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL;
            vlc_playlist_SetPlaybackOrder(playlist, order_mode);
        }
        msg_print(intf, "Setting random to %s", b_value ? "true" : "false");
    }
    else if (!strcmp( psz_cmd, "goto" ) )
    {
        long long llindex = atoll(newval.psz_string);
        size_t index = (size_t)llindex;
        size_t count = vlc_playlist_Count(playlist);
        if (llindex < 0)
            msg_print(intf, _("Error: `goto' needs an argument greater or equal to zero."));
        else if (index < count)
            vlc_playlist_PlayAt(playlist, index);
        else
            msg_print(intf,
                      vlc_ngettext("Playlist has only %zu element",
                                   "Playlist has only %zu elements", count),
                      count);
    }
    else if ((!strcmp(psz_cmd, "add") || !strcmp(psz_cmd, "enqueue")) &&
             newval.psz_string && *newval.psz_string)
    {
        input_item_t *p_item = parse_MRL( newval.psz_string );

        if( p_item )
        {
            msg_print(intf, "Trying to %s %s to playlist.", psz_cmd,
                      newval.psz_string);

            size_t count = vlc_playlist_Count(playlist);
            int ret = vlc_playlist_InsertOne(playlist, count, p_item);
            input_item_Release(p_item);
            if (ret != VLC_SUCCESS)
                goto end;

            if (!strcmp(psz_cmd, "add"))
                vlc_playlist_PlayAt(playlist, count);
        }
    }
    /*
     * sanity check
     */
    else
        msg_print(intf, "unknown command!");

end:
    vlc_playlist_Unlock(playlist);
}