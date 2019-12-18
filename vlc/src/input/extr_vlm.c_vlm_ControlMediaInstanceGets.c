#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlm_t ;
struct TYPE_10__ {int i_instance; TYPE_3__** instance; } ;
typedef  TYPE_1__ vlm_media_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  f_rate; int /*<<< orphan*/  b_paused; int /*<<< orphan*/  d_position; void* i_length; void* i_time; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_2__ vlm_media_instance_t ;
struct TYPE_12__ {int /*<<< orphan*/  player; scalar_t__ psz_name; } ;
typedef  TYPE_3__ vlm_media_instance_sys_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  TAB_INIT (int,TYPE_2__**) ; 
 void* US_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 
 int /*<<< orphan*/  vlc_player_GetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_GetPosition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_GetRate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_GetTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_IsPaused (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlm_ControlMediaGetById (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlm_media_instance_New () ; 

__attribute__((used)) static int vlm_ControlMediaInstanceGets( vlm_t *p_vlm, int64_t id, vlm_media_instance_t ***ppp_idsc, int *pi_instance )
{
    vlm_media_sys_t *p_media = vlm_ControlMediaGetById( p_vlm, id );
    vlm_media_instance_t **pp_idsc;
    int                              i_idsc;

    if( !p_media )
        return VLC_EGENERIC;

    TAB_INIT( i_idsc, pp_idsc );
    for( int i = 0; i < p_media->i_instance; i++ )
    {
        vlm_media_instance_sys_t *p_instance = p_media->instance[i];
        vlm_media_instance_t *p_idsc = vlm_media_instance_New();
        if( p_instance->psz_name )
            p_idsc->psz_name = strdup( p_instance->psz_name );
        vlc_player_Lock(p_instance->player);
        p_idsc->i_time = US_FROM_VLC_TICK(vlc_player_GetTime(p_instance->player));
        p_idsc->i_length = US_FROM_VLC_TICK(vlc_player_GetLength(p_instance->player));
        p_idsc->d_position = vlc_player_GetPosition(p_instance->player);
        p_idsc->b_paused = vlc_player_IsPaused(p_instance->player);
        p_idsc->f_rate = vlc_player_GetRate(p_instance->player);
        vlc_player_Unlock(p_instance->player);

        TAB_APPEND( i_idsc, pp_idsc, p_idsc );
    }
    *ppp_idsc = pp_idsc;
    *pi_instance = i_idsc;
    return VLC_SUCCESS;
}