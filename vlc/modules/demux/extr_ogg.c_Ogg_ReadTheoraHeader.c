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
struct TYPE_9__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_7__ {unsigned int i_frame_rate; unsigned int i_frame_rate_base; } ;
struct TYPE_8__ {int i_bitrate; TYPE_1__ video; } ;
struct TYPE_10__ {int b_force_backup; int i_first_frame_index; int /*<<< orphan*/  dts; scalar_t__ i_granule_shift; TYPE_2__ fmt; } ;
typedef  TYPE_4__ logical_stream_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 unsigned int __MAX (unsigned int,int) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static bool Ogg_ReadTheoraHeader( logical_stream_t *p_stream,
                                  ogg_packet *p_oggpacket )
{
    bs_t bitstream;
    unsigned int i_fps_numerator;
    unsigned int i_fps_denominator;
    int i_keyframe_frequency_force;
    int i_major;
    int i_minor;
    int i_subminor;
    int i_version;

    /* Signal that we want to keep a backup of the theora
     * stream headers. They will be used when switching between
     * audio streams. */
    p_stream->b_force_backup = true;

    /* Cheat and get additionnal info ;) */
    bs_init( &bitstream, p_oggpacket->packet, p_oggpacket->bytes );
    bs_skip( &bitstream, 56 );

    i_major = bs_read( &bitstream, 8 ); /* major version num */
    i_minor = bs_read( &bitstream, 8 ); /* minor version num */
    i_subminor = bs_read( &bitstream, 8 ); /* subminor version num */

    bs_read( &bitstream, 16 ) /*<< 4*/; /* width */
    bs_read( &bitstream, 16 ) /*<< 4*/; /* height */
    bs_read( &bitstream, 24 ); /* frame width */
    bs_read( &bitstream, 24 ); /* frame height */
    bs_read( &bitstream, 8 ); /* x offset */
    bs_read( &bitstream, 8 ); /* y offset */

    i_fps_numerator = bs_read( &bitstream, 32 );
    i_fps_denominator = bs_read( &bitstream, 32 );
    i_fps_denominator = __MAX( i_fps_denominator, 1 );
    bs_read( &bitstream, 24 ); /* aspect_numerator */
    bs_read( &bitstream, 24 ); /* aspect_denominator */

    p_stream->fmt.video.i_frame_rate = i_fps_numerator;
    p_stream->fmt.video.i_frame_rate_base = i_fps_denominator;

    bs_read( &bitstream, 8 ); /* colorspace */
    p_stream->fmt.i_bitrate = bs_read( &bitstream, 24 );
    bs_read( &bitstream, 6 ); /* quality */

    i_keyframe_frequency_force = 1 << bs_read( &bitstream, 5 );

    /* granule_shift = i_log( frequency_force -1 ) */
    p_stream->i_granule_shift = 0;
    i_keyframe_frequency_force--;
    while( i_keyframe_frequency_force )
    {
        p_stream->i_granule_shift++;
        i_keyframe_frequency_force >>= 1;
    }

    i_version = i_major * 1000000 + i_minor * 1000 + i_subminor;
    p_stream->i_first_frame_index = (i_version >= 3002001) ? 1 : 0;
    if ( !i_fps_denominator || !i_fps_numerator )
        return false;
    date_Init( &p_stream->dts, i_fps_numerator, i_fps_denominator );

    return true;
}