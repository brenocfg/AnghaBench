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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_STRING ; 
 int /*<<< orphan*/  config_PutPsz (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetURI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
playlist_bookmark_Set(intf_thread_t *intf,
                      vlc_playlist_t *playlist, char *name, int id)
{
    var_Create(intf, name, VLC_VAR_STRING | VLC_VAR_DOINHERIT);
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);
    input_item_t *item = vlc_player_GetCurrentMedia(player);
    if (item)
    {
        char *uri = input_item_GetURI(item);
        config_PutPsz(name, uri);
        msg_Info(intf, "setting playlist bookmark %i to %s", id, uri);
        free(uri);
    }
}