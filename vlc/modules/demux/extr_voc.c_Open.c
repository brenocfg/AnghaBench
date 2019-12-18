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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  pts; int /*<<< orphan*/ * p_es; scalar_t__ i_loop_count; scalar_t__ i_block_end; scalar_t__ i_block_start; scalar_t__ i_silence_countdown; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int GetWLE (int /*<<< orphan*/  const*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  ct_header ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    const uint8_t *p_buf;
    uint16_t    i_data_offset, i_version;

    if( vlc_stream_Peek( p_demux->s, &p_buf, 26 ) < 26 )
        return VLC_EGENERIC;

    if( memcmp( p_buf, ct_header, 20 ) )
        return VLC_EGENERIC;
    p_buf += 20;

    i_data_offset = GetWLE( p_buf );
    if ( i_data_offset < 26 /* not enough room for full VOC header */ )
        return VLC_EGENERIC;
    p_buf += 2;

    i_version = GetWLE( p_buf );
    if( ( i_version != 0x10A ) && ( i_version != 0x114 ) )
        return VLC_EGENERIC; /* unknown VOC version */
    p_buf += 2;

    if( GetWLE( p_buf ) != (uint16_t)(0x1234 + ~i_version) )
        return VLC_EGENERIC;

    /* We have a valid VOC header */
    msg_Dbg( p_demux, "CT Voice file v%d.%d", i_version >> 8,
             i_version & 0xff );

    /* skip VOC header */
    if( vlc_stream_Read( p_demux->s, NULL, i_data_offset ) < i_data_offset )
        return VLC_EGENERIC;

    demux_sys_t *p_sys = vlc_obj_malloc( p_this, sizeof (*p_sys) );
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    p_sys->i_silence_countdown = p_sys->i_block_start = p_sys->i_block_end =
    p_sys->i_loop_count = 0;
    p_sys->p_es = NULL;

    date_Init( &p_sys->pts, 1, 1 );
    date_Set( &p_sys->pts, VLC_TICK_0 );

    es_format_Init( &p_sys->fmt, AUDIO_ES, 0 );
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;
    p_demux->p_sys = p_sys;

    return VLC_SUCCESS;
}