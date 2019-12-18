#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;
struct TYPE_21__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_22__ {int b_indexloaded; unsigned int i_track; TYPE_16__** track; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_23__ {unsigned int i_size; TYPE_3__* p_entry; } ;
typedef  TYPE_6__ avi_index_t ;
struct TYPE_24__ {int i_flags; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_lengthtotal; scalar_t__ i_pos; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_7__ avi_entry_t ;
struct TYPE_25__ {unsigned int i_entry_count; TYPE_2__* entry; } ;
typedef  TYPE_8__ avi_chunk_idx1_t ;
struct TYPE_20__ {unsigned int i_lengthtotal; int /*<<< orphan*/  i_pos; } ;
struct TYPE_19__ {int i_flags; int /*<<< orphan*/  i_length; scalar_t__ i_pos; int /*<<< orphan*/  i_fourcc; } ;
struct TYPE_18__ {int i_cat; } ;
struct TYPE_17__ {scalar_t__ i_samplesize; TYPE_1__ fmt; } ;

/* Variables and functions */
 int AVIIF_FIXKEYFRAME ; 
 int /*<<< orphan*/  AVI_GetDPTS (TYPE_16__*,unsigned int) ; 
 scalar_t__ AVI_IndexFind_idx1 (TYPE_4__*,TYPE_8__**,scalar_t__*) ; 
 int /*<<< orphan*/  AVI_ParseStreamHeader (int /*<<< orphan*/ ,unsigned int*,int*) ; 
 int UNKNOWN_ES ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  avi_index_Append (TYPE_6__*,scalar_t__*,TYPE_7__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AVI_IndexLoad_idx1( demux_t *p_demux,
                               avi_index_t p_index[], uint64_t *pi_last_offset )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    avi_chunk_idx1_t *p_idx1;
    uint64_t         i_offset;
    if( AVI_IndexFind_idx1( p_demux, &p_idx1, &i_offset ) )
        return VLC_EGENERIC;

    p_sys->b_indexloaded = true;

    for( unsigned i_index = 0; i_index < p_idx1->i_entry_count; i_index++ )
    {
        enum es_format_category_e i_cat;
        unsigned i_stream;

        AVI_ParseStreamHeader( p_idx1->entry[i_index].i_fourcc,
                               &i_stream,
                               &i_cat );
        if( i_stream < p_sys->i_track &&
            (i_cat == p_sys->track[i_stream]->fmt.i_cat || i_cat == UNKNOWN_ES ) )
        {
            avi_entry_t index;
            index.i_id     = p_idx1->entry[i_index].i_fourcc;
            index.i_flags  = p_idx1->entry[i_index].i_flags&(~AVIIF_FIXKEYFRAME);
            index.i_pos    = p_idx1->entry[i_index].i_pos + i_offset;
            index.i_length = p_idx1->entry[i_index].i_length;
            index.i_lengthtotal = index.i_length;

            avi_index_Append( &p_index[i_stream], pi_last_offset, &index );
        }
    }

#ifdef AVI_DEBUG
    for( unsigned i_index = 0; i_index< p_idx1->i_entry_count && i_index < p_sys->i_track; i_index++ )
    {
        for( unsigned i = 0; i < p_index[i_index].i_size; i++ )
        {
            vlc_tick_t i_length;
            if( p_sys->track[i_index]->i_samplesize )
            {
                i_length = AVI_GetDPTS( p_sys->track[i_index],
                                        p_index[i_index].p_entry[i].i_lengthtotal );
            }
            else
            {
                i_length = AVI_GetDPTS( p_sys->track[i_index], i );
            }
            msg_Dbg( p_demux, "index stream %d @%ld time %ld", i_index,
                     p_index[i_index].p_entry[i].i_pos, i_length );
        }
    }
#endif
    return VLC_SUCCESS;
}