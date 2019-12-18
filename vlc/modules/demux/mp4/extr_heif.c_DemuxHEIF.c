#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {int /*<<< orphan*/ * p_infe; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * p_shared_header; TYPE_4__* (* BOXDATA ) (int /*<<< orphan*/ ) ;} ;
struct heif_private_t {scalar_t__ i_end_display_time; scalar_t__ i_pcr; scalar_t__ i_image_duration; int b_seekpoint_changed; scalar_t__ id; TYPE_1__ current; int /*<<< orphan*/ * p_root; } ;
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_16__ {int /*<<< orphan*/  out; scalar_t__ p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_17__ {scalar_t__ i_dts; scalar_t__ i_pts; scalar_t__ i_length; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_18__ {scalar_t__ item_type; int /*<<< orphan*/  i_item_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  i_item_id; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_infe ; 
 int /*<<< orphan*/  BLOCK_FLAG_END_OF_SEQUENCE ; 
 TYPE_13__* BOXDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ DerivedImageAssembleGrid (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ES_OUT_GET_EMPTY ; 
 void* GetAtom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* MP4_BoxGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MatchInfeID ; 
 int /*<<< orphan*/  MatchPureImage ; 
 TYPE_3__* ReadItemExtents (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupPicture (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ es_out_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  p_infe ; 
 TYPE_4__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_4__* stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DemuxHEIF( demux_t *p_demux )
{
    struct heif_private_t *p_sys = (void *) p_demux->p_sys;

    /* Displaying a picture */
    if( p_sys->i_end_display_time > 0 )
    {
        bool b_empty;
        es_out_Control( p_demux->out, ES_OUT_GET_EMPTY, &b_empty );
        if( !b_empty || vlc_tick_now() <= p_sys->i_end_display_time )
        {
            vlc_tick_sleep( VLC_TICK_FROM_MS(40) );
            return VLC_DEMUXER_SUCCESS;
        }
        p_sys->i_end_display_time = 0;
    }

    /* Reset prev pic params */
    p_sys->current.p_shared_header = NULL;

    /* First or next picture */
    if( !p_sys->current.p_infe )
    {
        MP4_Box_t *p_pitm = MP4_BoxGet( p_sys->p_root, "meta/pitm" );
        if( !p_pitm )
            return VLC_DEMUXER_EOF;

        p_sys->current.p_infe = GetAtom( p_sys->p_root, NULL,
                                         ATOM_infe, "meta/iinf/infe",
                                         MatchInfeID, &BOXDATA(p_pitm)->i_item_id );
    }
    else
    {
        p_sys->current.p_infe = GetAtom( p_sys->p_root, p_sys->current.p_infe,
                                         ATOM_infe, "meta/iinf/infe",
                                         MatchPureImage, p_sys->p_root );
    }

    if( !p_sys->current.p_infe )
        return VLC_DEMUXER_EOF;

    const uint32_t i_current_item_id = p_sys->current.BOXDATA(p_infe)->i_item_id;
    const MP4_Box_t *p_ipco = MP4_BoxGet( p_sys->p_root, "meta/iprp/ipco" );
    if( !p_ipco )
        return VLC_DEMUXER_EOF;

    es_format_t fmt;
    es_format_Init(&fmt, UNKNOWN_ES, 0);

    block_t *p_block = NULL;
    if( p_sys->current.BOXDATA(p_infe)->item_type == VLC_FOURCC('g','r','i','d') )
    {
        if( DerivedImageAssembleGrid( p_demux, i_current_item_id,
                                      &fmt, &p_block ) != VLC_SUCCESS )
        {
            es_format_Clean( &fmt );
            return VLC_DEMUXER_SUCCESS;
        }
    }
    else
    {
        if( SetupPicture( p_demux, p_sys->current.p_infe,
                          &fmt, &p_sys->current.p_shared_header ) != VLC_SUCCESS )
        {
            es_format_Clean( &fmt );
            return VLC_DEMUXER_SUCCESS;
        }

        p_block = ReadItemExtents( p_demux, i_current_item_id,
                                   p_sys->current.p_shared_header );
        if( !p_block )
        {
            es_format_Clean( &fmt );
            return VLC_DEMUXER_SUCCESS; /* Goto next picture */
        }
    }

    es_format_Clean( &p_sys->current.fmt );
    es_format_Copy( &p_sys->current.fmt, &fmt );
    es_format_Clean( &fmt );
    if( p_sys->id )
        es_out_Del( p_demux->out, p_sys->id );
    p_sys->id = es_out_Add( p_demux->out, &p_sys->current.fmt );

    if( !p_sys->id )
    {
        p_sys->current.p_infe = NULL; /* Goto next picture */
        return VLC_DEMUXER_SUCCESS;
    }

    if( p_sys->i_pcr == VLC_TICK_INVALID )
    {
        p_sys->i_pcr = VLC_TICK_0;
        es_out_SetPCR( p_demux->out, p_sys->i_pcr );
    }

    p_block->i_dts = p_block->i_pts = p_sys->i_pcr;
    p_block->i_length = p_sys->i_image_duration;

    p_block->i_flags |= BLOCK_FLAG_END_OF_SEQUENCE;

    p_sys->i_end_display_time = vlc_tick_now() + p_block->i_length;
    p_sys->b_seekpoint_changed = true;

    p_sys->i_pcr = p_block->i_dts + p_block->i_length;
    es_out_Send( p_demux->out, p_sys->id, p_block );
    es_out_SetPCR( p_demux->out, p_sys->i_pcr );

    return VLC_DEMUXER_SUCCESS;
}