#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vod_t ;
struct TYPE_23__ {int /*<<< orphan*/  media; int /*<<< orphan*/  i_media; int /*<<< orphan*/  i_id; TYPE_5__* p_vod; } ;
typedef  TYPE_3__ vlm_t ;
struct TYPE_24__ {int /*<<< orphan*/  psz_name; scalar_t__ b_vod; } ;
typedef  TYPE_4__ vlm_media_t ;
struct TYPE_26__ {int /*<<< orphan*/  psz_name; scalar_t__ id; } ;
struct TYPE_22__ {int /*<<< orphan*/ * p_media; int /*<<< orphan*/  p_item; } ;
struct TYPE_21__ {int /*<<< orphan*/ * logger; } ;
struct TYPE_25__ {TYPE_6__ cfg; int /*<<< orphan*/  instance; int /*<<< orphan*/  i_instance; TYPE_2__ vod; TYPE_1__ obj; int /*<<< orphan*/  pf_media_control; TYPE_3__* p_data; int /*<<< orphan*/  p_module; } ;
typedef  TYPE_5__ vlm_media_sys_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int asprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_need_var (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * vlc_LogHeaderCreate (int /*<<< orphan*/ *,char*) ; 
 void* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_5__*) ; 
 scalar_t__ vlm_ControlMediaGetByName (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlm_MediaDescriptionCheck (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vlm_MediaVodControl ; 
 int vlm_OnMediaUpdate (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vlm_SendEventMediaAdded (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlm_media_Copy (TYPE_6__*,TYPE_4__*) ; 

__attribute__((used)) static int vlm_ControlMediaAdd( vlm_t *p_vlm, vlm_media_t *p_cfg, int64_t *p_id )
{
    vlm_media_sys_t *p_media;
    char *header;

    if( vlm_MediaDescriptionCheck( p_vlm, p_cfg ) || vlm_ControlMediaGetByName( p_vlm, p_cfg->psz_name ) )
    {
        msg_Err( p_vlm, "invalid media description" );
        return VLC_EGENERIC;
    }
    /* Check if we need to load the VOD server */
    if( p_cfg->b_vod && !p_vlm->p_vod )
    {
        p_vlm->p_vod = vlc_custom_create( VLC_OBJECT(p_vlm), sizeof( vod_t ),
                                          "vod server" );
        p_vlm->p_vod->p_module = module_need_var( p_vlm->p_vod, "vod server", "vod-server" );
        if( !p_vlm->p_vod->p_module )
        {
            msg_Err( p_vlm, "cannot find vod server" );
            vlc_object_delete(p_vlm->p_vod);
            p_vlm->p_vod = NULL;
            return VLC_EGENERIC;
        }

        p_vlm->p_vod->p_data = p_vlm;
        p_vlm->p_vod->pf_media_control = vlm_MediaVodControl;
    }

    p_media = vlc_custom_create( VLC_OBJECT(p_vlm), sizeof( *p_media ),
                                 "media" );
    if( !p_media )
        return VLC_ENOMEM;

    if( asprintf( &header, _("Media: %s"), p_cfg->psz_name ) == -1 )
    {
        vlc_object_delete(p_media);
        return VLC_ENOMEM;
    }

    p_media->obj.logger = vlc_LogHeaderCreate( p_media->obj.logger, header );
    free( header );

    if( p_media->obj.logger == NULL )
    {
        vlc_object_delete(p_media);
        return VLC_ENOMEM;
    }

    vlm_media_Copy( &p_media->cfg, p_cfg );
    p_media->cfg.id = p_vlm->i_id++;
    /* FIXME do we do something here if enabled is true ? */

    p_media->vod.p_item = input_item_New( NULL, NULL );

    p_media->vod.p_media = NULL;
    TAB_INIT( p_media->i_instance, p_media->instance );

    /* */
    TAB_APPEND( p_vlm->i_media, p_vlm->media, p_media );

    if( p_id )
        *p_id = p_media->cfg.id;

    /* */
    vlm_SendEventMediaAdded( p_vlm, p_media->cfg.id, p_media->cfg.psz_name );
    return vlm_OnMediaUpdate( p_vlm, p_media );
}