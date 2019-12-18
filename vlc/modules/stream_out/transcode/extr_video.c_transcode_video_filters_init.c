#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_10__ {scalar_t__ p_spu; int /*<<< orphan*/  encoder; void* p_uf_chain; void* p_f_chain; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
struct TYPE_9__ {char* psz_deinterlace; scalar_t__ psz_spu_sources; int /*<<< orphan*/  b_reorient; int /*<<< orphan*/ * p_deinterlace_cfg; } ;
struct TYPE_11__ {TYPE_1__ video; scalar_t__ psz_filters; } ;
typedef  TYPE_3__ sout_filters_config_t ;
struct TYPE_12__ {TYPE_2__* sys; int /*<<< orphan*/ * video; } ;
typedef  TYPE_4__ filter_owner_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  debug_format (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  filter_chain_AppendFilter (void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  filter_chain_AppendFromString (void*,scalar_t__) ; 
 int /*<<< orphan*/ * filter_chain_GetFmtOut (void*) ; 
 void* filter_chain_NewVideo (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  filter_chain_Reset (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spu_ChangeSources (scalar_t__,scalar_t__) ; 
 scalar_t__ spu_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transcode_encoder_update_format_in (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  transcode_filter_video_cbs ; 
 scalar_t__ transcode_video_set_conversions (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transcode_video_filters_init( sout_stream_t *p_stream,
                                         const sout_filters_config_t *p_cfg,
                                         bool b_master_sync,
                                         const es_format_t *p_src,
                                         const es_format_t *p_dst,
                                         sout_stream_id_sys_t *id )
{
    /* Build chain */
    filter_owner_t owner = {
        .video = &transcode_filter_video_cbs,
        .sys = id,
    };
    id->p_f_chain = filter_chain_NewVideo( p_stream, false, &owner );
    if( !id->p_f_chain )
        return VLC_EGENERIC;
    filter_chain_Reset( id->p_f_chain, p_src, p_src );

    /* Deinterlace */
    if( p_cfg->video.psz_deinterlace != NULL )
    {
        filter_chain_AppendFilter( id->p_f_chain,
                                   p_cfg->video.psz_deinterlace,
                                   p_cfg->video.p_deinterlace_cfg,
                                   p_src );
        p_src = filter_chain_GetFmtOut( id->p_f_chain );
    }

    if( b_master_sync )
    {
        filter_chain_AppendFilter( id->p_f_chain, "fps", NULL, p_dst );
        p_src = filter_chain_GetFmtOut( id->p_f_chain );
    }

    /* Chroma and other conversions */
    if( transcode_video_set_conversions( p_stream, id, &p_src, p_dst,
                                         p_cfg->video.b_reorient ) != VLC_SUCCESS )
        return VLC_EGENERIC;

    /* User filters */
    if( p_cfg->psz_filters )
    {
        msg_Dbg( p_stream, "adding user filters" );
        id->p_uf_chain = filter_chain_NewVideo( p_stream, true, &owner );
        if(!id->p_uf_chain)
            return VLC_EGENERIC;
        filter_chain_Reset( id->p_uf_chain, p_src, p_dst );
        filter_chain_AppendFromString( id->p_uf_chain, p_cfg->psz_filters );
        p_src = filter_chain_GetFmtOut( id->p_uf_chain );
        debug_format( p_stream, p_src );
   }

    /* Update encoder so it matches filters output */
    transcode_encoder_update_format_in( id->encoder, p_src );

    /* SPU Sources */
    if( p_cfg->video.psz_spu_sources )
    {
        if( id->p_spu || (id->p_spu = spu_Create( p_stream, NULL )) )
            spu_ChangeSources( id->p_spu, p_cfg->video.psz_spu_sources );
    }

    return VLC_SUCCESS;
}