#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlm_t ;
struct TYPE_12__ {int i_input; char* psz_output; int i_option; char** ppsz_option; char** ppsz_input; int /*<<< orphan*/  psz_name; scalar_t__ b_vod; int /*<<< orphan*/  b_enabled; } ;
typedef  TYPE_2__ vlm_media_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_media; } ;
struct TYPE_13__ {TYPE_2__ cfg; int /*<<< orphan*/  instance; int /*<<< orphan*/  i_instance; TYPE_1__ vod; } ;
typedef  TYPE_3__ vlm_media_sys_t ;
struct TYPE_14__ {int i_index; int /*<<< orphan*/  p_item; int /*<<< orphan*/ * player; int /*<<< orphan*/  p_parent; } ;
typedef  TYPE_4__ vlm_media_instance_sys_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_INPUT_OPTION_TRUSTED ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int asprintf (char**,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_AddOption (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_SetURI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ ,char*,char const*) ; 
 char* vlc_path2uri (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_player_IsPaused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SetCurrentMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* vlm_ControlMediaGetById (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* vlm_ControlMediaInstanceGetByName (TYPE_3__*,char const*) ; 
 TYPE_4__* vlm_MediaInstanceNew (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  vlm_SendEventMediaInstanceStarted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlm_SendEventMediaInstanceStopped (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlm_ControlMediaInstanceStart( vlm_t *p_vlm, int64_t id, const char *psz_id, int i_input_index, const char *psz_vod_output )
{
    vlm_media_sys_t *p_media = vlm_ControlMediaGetById( p_vlm, id );
    vlm_media_instance_sys_t *p_instance;

    if( !p_media || !p_media->cfg.b_enabled || p_media->cfg.i_input <= 0 )
        return VLC_EGENERIC;

    /* TODO support multiple input for VOD with sout-keep ? */

    if( ( p_media->cfg.b_vod && !psz_vod_output ) || ( !p_media->cfg.b_vod && psz_vod_output ) )
        return VLC_EGENERIC;

    if( i_input_index < 0 || i_input_index >= p_media->cfg.i_input )
        return VLC_EGENERIC;

    p_instance = vlm_ControlMediaInstanceGetByName( p_media, psz_id );
    if( !p_instance )
    {
        vlm_media_t *p_cfg = &p_media->cfg;

        p_instance = vlm_MediaInstanceNew( p_media, psz_id );
        if( !p_instance )
            return VLC_ENOMEM;

        if ( p_cfg->b_vod )
        {
            var_Create( p_instance->p_parent, "vod-media", VLC_VAR_ADDRESS );
            var_SetAddress( p_instance->p_parent, "vod-media",
                            p_media->vod.p_media );
            var_Create( p_instance->p_parent, "vod-session", VLC_VAR_STRING );
            var_SetString( p_instance->p_parent, "vod-session", psz_id );
        }

        if( p_cfg->psz_output != NULL || psz_vod_output != NULL )
        {
            char *psz_buffer;
            if( asprintf( &psz_buffer, "sout=%s%s%s",
                      p_cfg->psz_output ? p_cfg->psz_output : "",
                      (p_cfg->psz_output && psz_vod_output) ? ":" : psz_vod_output ? "#" : "",
                      psz_vod_output ? psz_vod_output : "" ) != -1 )
            {
                input_item_AddOption( p_instance->p_item, psz_buffer, VLC_INPUT_OPTION_TRUSTED );
                free( psz_buffer );
            }
        }

        for( int i = 0; i < p_cfg->i_option; i++ )
            input_item_AddOption( p_instance->p_item, p_cfg->ppsz_option[i], VLC_INPUT_OPTION_TRUSTED );
        TAB_APPEND( p_media->i_instance, p_media->instance, p_instance );
    }

    /* Stop old instance */
    vlc_player_t *player = p_instance->player;
    vlc_player_Lock(player);
    if (vlc_player_GetCurrentMedia(player))
    {
        if( p_instance->i_index == i_input_index )
        {
            if (vlc_player_IsPaused(player))
                vlc_player_Resume(player);
            return VLC_SUCCESS;
        }

        vlc_player_Stop(player);
        vlc_player_Unlock(player);
        vlm_SendEventMediaInstanceStopped( p_vlm, id, p_media->cfg.psz_name );
        vlc_player_Lock(player);
    }

    /* Start new one */
    p_instance->i_index = i_input_index;
    if( strstr( p_media->cfg.ppsz_input[p_instance->i_index], "://" ) == NULL )
    {
        char *psz_uri = vlc_path2uri(
                          p_media->cfg.ppsz_input[p_instance->i_index], NULL );
        input_item_SetURI( p_instance->p_item, psz_uri ) ;
        free( psz_uri );
    }
    else
        input_item_SetURI( p_instance->p_item, p_media->cfg.ppsz_input[p_instance->i_index] ) ;

    vlc_player_SetCurrentMedia(player, p_instance->p_item);
    vlc_player_Start(player);
    vlc_player_Unlock(player);

    vlm_SendEventMediaInstanceStarted( p_vlm, id, p_media->cfg.psz_name );

    return VLC_SUCCESS;
}