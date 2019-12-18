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
struct TYPE_11__ {size_t i_chunk; size_t i_chunk_count; int b_ok; int b_selected; unsigned int i_sample; TYPE_1__* chunk; int /*<<< orphan*/ * p_es; int /*<<< orphan*/  i_track_ID; } ;
typedef  TYPE_2__ mp4_track_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_10__ {scalar_t__ i_sample_description_index; scalar_t__ i_sample_first; scalar_t__ i_sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_GET_ES_STATE ; 
 int /*<<< orphan*/  ES_OUT_SET_ES ; 
 scalar_t__ TrackCreateES (TYPE_3__*,TYPE_2__*,unsigned int,int /*<<< orphan*/ **) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int TrackGotoChunkSample( demux_t *p_demux, mp4_track_t *p_track,
                                 unsigned int i_chunk, unsigned int i_sample )
{
    bool b_reselect = false;

    /* now see if actual es is ok */
    if( p_track->i_chunk >= p_track->i_chunk_count ||
        p_track->chunk[p_track->i_chunk].i_sample_description_index !=
            p_track->chunk[i_chunk].i_sample_description_index )
    {
        msg_Warn( p_demux, "recreate ES for track[Id 0x%x]",
                  p_track->i_track_ID );

        es_out_Control( p_demux->out, ES_OUT_GET_ES_STATE,
                        p_track->p_es, &b_reselect );

        es_out_Del( p_demux->out, p_track->p_es );

        p_track->p_es = NULL;

        if( TrackCreateES( p_demux, p_track, i_chunk, &p_track->p_es ) )
        {
            msg_Err( p_demux, "cannot create es for track[Id 0x%x]",
                     p_track->i_track_ID );

            p_track->b_ok       = false;
            p_track->b_selected = false;
            return VLC_EGENERIC;
        }
    }

    /* select again the new decoder */
    if( b_reselect )
    {
        es_out_Control( p_demux->out, ES_OUT_SET_ES, p_track->p_es );
    }

    p_track->i_chunk    = i_chunk;
    p_track->chunk[i_chunk].i_sample = i_sample - p_track->chunk[i_chunk].i_sample_first;
    p_track->i_sample   = i_sample;

    return p_track->b_selected ? VLC_SUCCESS : VLC_EGENERIC;
}