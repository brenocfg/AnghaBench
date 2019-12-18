#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  unsigned int uint32_t ;
struct TYPE_13__ {unsigned int i_desc_bytes; int /*<<< orphan*/  i_frames; int /*<<< orphan*/  i_samples; int /*<<< orphan*/  i_bytes; } ;
typedef  TYPE_4__ frame_span_t ;
struct TYPE_14__ {int /*<<< orphan*/  s; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_11__ {scalar_t__ i_frame_length; scalar_t__ i_bytes_per_frame; } ;
struct TYPE_12__ {TYPE_2__ audio; } ;
struct TYPE_10__ {scalar_t__ i_descriptions_start; } ;
struct TYPE_15__ {TYPE_3__ fmt; TYPE_1__ packet_table; } ;
typedef  TYPE_6__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ ParseVarLenInteger (int /*<<< orphan*/  const*,int,scalar_t__*,unsigned int*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int FrameSpanAddDescription( demux_t *p_demux, uint64_t i_desc_offset, frame_span_t *span )
{
    demux_sys_t *p_sys  = p_demux->p_sys;

    /* Avoid seeking + peeking for simple case (PCM) */
    if( p_sys->fmt.audio.i_bytes_per_frame && p_sys->fmt.audio.i_frame_length )
    {
        span->i_bytes += p_sys->fmt.audio.i_bytes_per_frame;
        span->i_samples += p_sys->fmt.audio.i_frame_length;
        span->i_frames++;
        return VLC_SUCCESS;
    }

    uint32_t i_desc_size = 0;

    if( vlc_stream_Seek( p_demux->s, p_sys->packet_table.i_descriptions_start + i_desc_offset ))
    {
        msg_Err( p_demux, "Couldn't seek packet description." );
        return VLC_EGENERIC;
    }

    const uint8_t *p_peek;
    int i_peek_len = vlc_stream_Peek( p_demux->s, &p_peek, 2 * 10 );
    /* Peeking the maximum number of bytes that two 64 bit numbers could use
     * (( 64 + 6 ) / 7 = 10). */
    if( i_peek_len < 0 )
        i_peek_len = 0;

    if( p_sys->fmt.audio.i_bytes_per_frame )
    {
        span->i_bytes += p_sys->fmt.audio.i_bytes_per_frame;
    }
    else
    {
        uint64_t i_size;
        uint32_t i_this_int;
        if( ParseVarLenInteger( p_peek, i_peek_len, &i_size, &i_this_int ))
        {
            return VLC_EGENERIC;
        }

        i_desc_size += i_this_int;
        span->i_bytes += i_size;
    }

    if( p_sys->fmt.audio.i_frame_length )
    {
        span->i_samples += p_sys->fmt.audio.i_frame_length;
    }
    else
    {
        if( i_desc_size >= (unsigned)i_peek_len )
        {
            return VLC_EGENERIC;
        }

        uint64_t i_num_samples;
        uint32_t i_this_int;
        if( ParseVarLenInteger( p_peek + i_desc_size, i_peek_len - i_desc_size, &i_num_samples, &i_this_int ))
        {
            return VLC_EGENERIC;
        }

        i_desc_size += i_this_int;
        span->i_samples += i_num_samples;
    }
    span->i_desc_bytes += i_desc_size;
    span->i_frames++;

    return VLC_SUCCESS;
}