#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlm_t ;
struct TYPE_8__ {int /*<<< orphan*/  psz_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  instance; int /*<<< orphan*/  i_instance; TYPE_1__ cfg; } ;
typedef  TYPE_2__ vlm_media_sys_t ;
struct TYPE_10__ {struct TYPE_10__* psz_name; int /*<<< orphan*/  p_item; int /*<<< orphan*/  p_parent; int /*<<< orphan*/  listener; int /*<<< orphan*/ * player; } ;
typedef  TYPE_3__ vlm_media_instance_sys_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Delete (int /*<<< orphan*/ *) ; 
 int vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlm_SendEventMediaInstanceStopped (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlm_MediaInstanceDelete( vlm_t *p_vlm, int64_t id, vlm_media_instance_sys_t *p_instance, vlm_media_sys_t *p_media )
{
    vlc_player_t *player = p_instance->player;

    vlc_player_Lock(player);
    vlc_player_RemoveListener(player, p_instance->listener);
    vlc_player_Stop(player);
    bool had_media = vlc_player_GetCurrentMedia(player);
    vlc_player_Unlock(player);
    vlc_player_Delete(player);

    if (had_media)
        vlm_SendEventMediaInstanceStopped( p_vlm, id, p_media->cfg.psz_name );
    vlc_object_delete(p_instance->p_parent);

    TAB_REMOVE( p_media->i_instance, p_media->instance, p_instance );
    input_item_Release( p_instance->p_item );
    free( p_instance->psz_name );
    free( p_instance );
}