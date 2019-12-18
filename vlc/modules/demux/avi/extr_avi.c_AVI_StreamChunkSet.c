#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_9__ {TYPE_4__** track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_7__ {unsigned int i_size; } ;
struct TYPE_10__ {unsigned int i_idxposc; TYPE_1__ idx; scalar_t__ i_idxposb; } ;
typedef  TYPE_4__ avi_track_t ;

/* Variables and functions */
 scalar_t__ AVI_StreamChunkFind (TYPE_2__*,unsigned int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int AVI_StreamChunkSet( demux_t *p_demux, unsigned int i_stream,
                               unsigned int i_ck )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    avi_track_t *p_stream = p_sys->track[i_stream];

    p_stream->i_idxposc = i_ck;
    p_stream->i_idxposb = 0;

    if(  i_ck >= p_stream->idx.i_size )
    {
        p_stream->i_idxposc = p_stream->idx.i_size - 1;
        do
        {
            p_stream->i_idxposc++;
            if( AVI_StreamChunkFind( p_demux, i_stream ) )
            {
                return VLC_EGENERIC;
            }

        } while( p_stream->i_idxposc < i_ck );
    }

    return VLC_SUCCESS;
}