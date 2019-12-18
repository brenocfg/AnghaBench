#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_36__ {TYPE_1__* p_es; } ;
typedef  TYPE_3__ ts_stream_t ;
struct TYPE_35__ {int i_size; TYPE_8__** p_elems; } ;
struct TYPE_40__ {TYPE_2__ objects; } ;
struct TYPE_37__ {TYPE_7__ od; } ;
typedef  TYPE_4__ ts_pmt_t ;
struct TYPE_30__ {int b_packetized; int /*<<< orphan*/  i_group; int /*<<< orphan*/  i_id; } ;
struct TYPE_38__ {scalar_t__ id; TYPE_10__ fmt; } ;
typedef  TYPE_5__ ts_es_t ;
struct TYPE_39__ {size_t i_size; } ;
typedef  TYPE_6__ sl_header_data ;
typedef  TYPE_7__ od_descriptors_t ;
struct TYPE_41__ {TYPE_9__* es_descr; } ;
typedef  TYPE_8__ od_descriptor_t ;
struct TYPE_34__ {int i_objectTypeIndication; int i_streamType; } ;
struct TYPE_42__ {TYPE_21__ dec_descr; scalar_t__ b_ok; int /*<<< orphan*/  i_es_id; int /*<<< orphan*/  sl_descr; } ;
typedef  TYPE_9__ es_mpeg4_descriptor_t ;
typedef  TYPE_10__ es_format_t ;
struct TYPE_31__ {int /*<<< orphan*/  out; TYPE_12__* p_sys; } ;
typedef  TYPE_11__ demux_t ;
struct TYPE_32__ {scalar_t__ seltype; int /*<<< orphan*/  i_pmt_es; } ;
typedef  TYPE_12__ demux_sys_t ;
struct TYPE_33__ {int /*<<< orphan*/  i_sl_es_id; TYPE_4__* p_program; } ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeODCommand (int /*<<< orphan*/ ,TYPE_7__*,size_t,int /*<<< orphan*/  const*) ; 
 TYPE_6__ DecodeSLHeader (size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int ES_DESCRIPTOR_COUNT ; 
 TYPE_9__* GetMPEG4DescByEsId (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* GetPMTESBySLEsId (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PROGRAM_ALL ; 
 scalar_t__ SetupISO14496LogicalStream (TYPE_11__*,TYPE_21__*,TYPE_10__*) ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  UpdatePESFilters (TYPE_11__*,int) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_11__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_10__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_IsSimilar (TYPE_10__*,TYPE_10__*) ; 
 scalar_t__ es_out_Add (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 

void SLPackets_Section_Handler( demux_t *p_demux,
                                const uint8_t *p_sectiondata, size_t i_sectiondata,
                                const uint8_t *p_payloaddata, size_t i_payloaddata,
                                void *p_pes_cbdata )
{
    VLC_UNUSED(p_sectiondata); VLC_UNUSED(i_sectiondata);
    demux_sys_t *p_sys = p_demux->p_sys;
    ts_stream_t *p_pes = (ts_stream_t *) p_pes_cbdata;
    ts_pmt_t *p_pmt = p_pes->p_es->p_program;

    const es_mpeg4_descriptor_t *p_mpeg4desc = GetMPEG4DescByEsId( p_pmt, p_pes->p_es->i_sl_es_id );
    if( p_mpeg4desc && p_mpeg4desc->dec_descr.i_objectTypeIndication == 0x01 &&
        p_mpeg4desc->dec_descr.i_streamType == 0x01 /* Object */ )
    {
        const uint8_t *p_data = p_payloaddata;
        size_t i_data = i_payloaddata;

        od_descriptors_t *p_ods = &p_pmt->od;
        sl_header_data header = DecodeSLHeader( i_data, p_data, &p_mpeg4desc->sl_descr );

        DecodeODCommand( VLC_OBJECT(p_demux), p_ods, i_data - header.i_size, &p_data[header.i_size] );
        bool b_changed = false;

        for( int i=0; i<p_ods->objects.i_size; i++ )
        {
            od_descriptor_t *p_od = p_ods->objects.p_elems[i];
            for( int j = 0; j < ES_DESCRIPTOR_COUNT && p_od->es_descr[j].b_ok; j++ )
            {
                p_mpeg4desc = &p_od->es_descr[j];
                ts_es_t *p_es = GetPMTESBySLEsId( p_pmt, p_mpeg4desc->i_es_id );
                es_format_t fmt;
                es_format_Init( &fmt, UNKNOWN_ES, 0 );

                if ( p_mpeg4desc && p_mpeg4desc->b_ok && p_es &&
                     SetupISO14496LogicalStream( p_demux, &p_mpeg4desc->dec_descr, &fmt ) &&
                     !es_format_IsSimilar( &fmt, &p_es->fmt ) )
                {
                    fmt.i_id = p_es->fmt.i_id;
                    fmt.i_group = p_es->fmt.i_group;
                    es_format_Clean( &p_es->fmt );
                    p_es->fmt = fmt;

                    if( p_es->id )
                    {
                        es_out_Del( p_demux->out, p_es->id );
                        p_sys->i_pmt_es--;
                    }
                    p_es->fmt.b_packetized = true; /* Split by access unit, no sync code */
                    p_es->id = es_out_Add( p_demux->out, &p_es->fmt );
                    if( p_es->id )
                        p_sys->i_pmt_es++;
                    b_changed = true;
                }
                else
                    es_format_Clean( &fmt );
            }
        }

        if( b_changed )
            UpdatePESFilters( p_demux, p_sys->seltype == PROGRAM_ALL );
    }
}