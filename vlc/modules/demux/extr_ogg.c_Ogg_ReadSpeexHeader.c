#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_12__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_4__ ogg_packet ;
struct TYPE_10__ {void* i_framesperpacket; void* i_framesize; } ;
struct TYPE_11__ {TYPE_2__ speex; } ;
struct TYPE_14__ {void* i_channels; void* i_rate; } ;
struct TYPE_9__ {void* i_bitrate; TYPE_6__ audio; } ;
struct TYPE_13__ {int b_force_backup; void* i_extra_headers_packets; TYPE_3__ special; TYPE_1__ fmt; int /*<<< orphan*/  dts; } ;
typedef  TYPE_5__ logical_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  fill_channels_info (TYPE_6__*) ; 
 int /*<<< orphan*/  oggpack_adv (int /*<<< orphan*/ *,int) ; 
 void* oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggpack_readinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Ogg_ReadSpeexHeader( logical_stream_t *p_stream,
                                 ogg_packet *p_oggpacket )
{
    oggpack_buffer opb;

    /* Signal that we want to keep a backup of the speex
     * stream headers. They will be used when switching between
     * audio streams. */
    p_stream->b_force_backup = true;

    /* Cheat and get additionnal info ;) */
    oggpack_readinit( &opb, p_oggpacket->packet, p_oggpacket->bytes);
    oggpack_adv( &opb, 224 );
    oggpack_adv( &opb, 32 ); /* speex_version_id */
    oggpack_adv( &opb, 32 ); /* header_size */
    p_stream->fmt.audio.i_rate = oggpack_read( &opb, 32 );
    if ( !p_stream->fmt.audio.i_rate )
        return false;
    date_Init( &p_stream->dts, p_stream->fmt.audio.i_rate, 1 );
    oggpack_adv( &opb, 32 ); /* mode */
    oggpack_adv( &opb, 32 ); /* mode_bitstream_version */
    p_stream->fmt.audio.i_channels = oggpack_read( &opb, 32 );
    fill_channels_info(&p_stream->fmt.audio);
    p_stream->fmt.i_bitrate = oggpack_read( &opb, 32 );
    p_stream->special.speex.i_framesize =
            oggpack_read( &opb, 32 ); /* frame_size */
    oggpack_adv( &opb, 32 ); /* vbr */
    p_stream->special.speex.i_framesperpacket =
            oggpack_read( &opb, 32 ); /* frames_per_packet */
    p_stream->i_extra_headers_packets = oggpack_read( &opb, 32 ); /* extra_headers */
    return true;
}