#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_11__ {TYPE_5__** track; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_9__ {int i_size; TYPE_1__* p_entry; } ;
struct TYPE_12__ {int i_idxposc; TYPE_2__ idx; scalar_t__ i_idxposb; } ;
typedef  TYPE_5__ avi_track_t ;
struct TYPE_8__ {scalar_t__ i_lengthtotal; scalar_t__ i_length; } ;

/* Variables and functions */
 scalar_t__ AVI_StreamChunkFind (TYPE_3__*,unsigned int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int __MIN (int,int) ; 

__attribute__((used)) static int AVI_StreamBytesSet( demux_t    *p_demux,
                               unsigned int i_stream,
                               uint64_t  i_byte )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    avi_track_t *p_stream = p_sys->track[i_stream];

    if( ( p_stream->idx.i_size > 0 )
        &&( i_byte < p_stream->idx.p_entry[p_stream->idx.i_size - 1].i_lengthtotal +
                p_stream->idx.p_entry[p_stream->idx.i_size - 1].i_length ) )
    {
        /* index is valid to find the ck */
        /* uses dichototmie to be fast enougth */
        int i_idxposc = __MIN( p_stream->i_idxposc, p_stream->idx.i_size - 1 );
        int i_idxmax  = p_stream->idx.i_size;
        int i_idxmin  = 0;
        for( ;; )
        {
            if( p_stream->idx.p_entry[i_idxposc].i_lengthtotal > i_byte )
            {
                i_idxmax  = i_idxposc ;
                i_idxposc = ( i_idxmin + i_idxposc ) / 2 ;
            }
            else
            {
                if( p_stream->idx.p_entry[i_idxposc].i_lengthtotal +
                        p_stream->idx.p_entry[i_idxposc].i_length <= i_byte)
                {
                    i_idxmin  = i_idxposc ;
                    i_idxposc = (i_idxmax + i_idxposc ) / 2 ;
                }
                else
                {
                    p_stream->i_idxposc = i_idxposc;
                    p_stream->i_idxposb = i_byte -
                            p_stream->idx.p_entry[i_idxposc].i_lengthtotal;
                    return VLC_SUCCESS;
                }
            }
        }

    }
    else
    {
        p_stream->i_idxposc = p_stream->idx.i_size - 1;
        p_stream->i_idxposb = 0;
        do
        {
            p_stream->i_idxposc++;
            if( AVI_StreamChunkFind( p_demux, i_stream ) )
            {
                return VLC_EGENERIC;
            }

        } while( p_stream->idx.p_entry[p_stream->i_idxposc].i_lengthtotal +
                    p_stream->idx.p_entry[p_stream->i_idxposc].i_length <= i_byte );

        p_stream->i_idxposb = i_byte -
                       p_stream->idx.p_entry[p_stream->i_idxposc].i_lengthtotal;
        return VLC_SUCCESS;
    }
}