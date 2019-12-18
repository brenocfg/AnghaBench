#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {TYPE_3__* p_es; } ;
typedef  TYPE_4__ ts_stream_t ;
struct TYPE_13__ {scalar_t__ i_current; } ;
struct TYPE_16__ {TYPE_2__ pcr; } ;
typedef  TYPE_5__ ts_pmt_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_17__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_6__ demux_t ;
struct TYPE_18__ {int* p_buffer; size_t i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_7__ block_t ;
struct TYPE_12__ {scalar_t__ i_codec; } ;
struct TYPE_14__ {scalar_t__ id; TYPE_5__* p_program; TYPE_1__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_SCALE (scalar_t__) ; 
 scalar_t__ GetDWBE (int*) ; 
 scalar_t__ VLC_CODEC_SCTE_27 ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

void SCTE27_Section_Callback( demux_t *p_demux,
                              const uint8_t *p_sectiondata, size_t i_sectiondata,
                              const uint8_t *p_payloaddata, size_t i_payloaddata,
                              void *p_pes_cb_data )
{
    VLC_UNUSED(p_payloaddata); VLC_UNUSED(i_payloaddata);
    ts_stream_t *p_pes = (ts_stream_t *) p_pes_cb_data;
    assert( p_pes->p_es->fmt.i_codec == VLC_CODEC_SCTE_27 );
    ts_pmt_t *p_pmt = p_pes->p_es->p_program;
    stime_t i_date = p_pmt->pcr.i_current;

    block_t *p_content = block_Alloc( i_sectiondata );
    if( unlikely(!p_content) || unlikely(!p_pes->p_es->id) )
        return;
    memcpy( p_content->p_buffer, p_sectiondata, i_sectiondata );

    /* We need to extract the truncated pts stored inside the payload */
    int i_index = 0;
    size_t i_offset = 4;
    if( p_content->p_buffer[3] & 0x40 )
    {
        i_index = ((p_content->p_buffer[7] & 0x0f) << 8) | /* segment number */
                p_content->p_buffer[8];
        i_offset += 5;
    }
    if( i_index == 0 && p_content->i_buffer > i_offset + 8 ) /* message body */
    {
        bool is_immediate = p_content->p_buffer[i_offset + 3] & 0x40;
        if( !is_immediate )
        {
            stime_t i_display_in = GetDWBE( &p_content->p_buffer[i_offset + 4] );
            if( i_display_in < i_date )
                i_date = i_display_in + (1ll << 32);
            else
                i_date = i_display_in;
        }

    }

    p_content->i_dts = p_content->i_pts = FROM_SCALE(i_date);
    //PCRFixHandle( p_demux, p_pmt, p_content );

    if( p_pes->p_es->id )
        es_out_Send( p_demux->out, p_pes->p_es->id, p_content );
    else
        block_Release( p_content );
}