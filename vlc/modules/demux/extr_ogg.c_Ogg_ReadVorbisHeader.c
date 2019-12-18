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
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_8__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_2__ ogg_packet ;
struct TYPE_10__ {void* i_rate; void* i_channels; } ;
struct TYPE_7__ {void* i_bitrate; TYPE_4__ audio; } ;
struct TYPE_9__ {int b_force_backup; TYPE_1__ fmt; int /*<<< orphan*/  dts; } ;
typedef  TYPE_3__ logical_stream_t ;

/* Variables and functions */
 void* INT32_MAX ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  fill_channels_info (TYPE_4__*) ; 
 int /*<<< orphan*/  oggpack_adv (int /*<<< orphan*/ *,int) ; 
 void* oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggpack_readinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Ogg_ReadVorbisHeader( logical_stream_t *p_stream,
                                  ogg_packet *p_oggpacket )
{
    oggpack_buffer opb;

    /* Signal that we want to keep a backup of the vorbis
     * stream headers. They will be used when switching between
     * audio streams. */
    p_stream->b_force_backup = true;

    /* Cheat and get additionnal info ;) */
    oggpack_readinit( &opb, p_oggpacket->packet, p_oggpacket->bytes);
    oggpack_adv( &opb, 88 );
    p_stream->fmt.audio.i_channels = oggpack_read( &opb, 8 );
    fill_channels_info(&p_stream->fmt.audio);
    p_stream->fmt.audio.i_rate = oggpack_read( &opb, 32 );
    if( p_stream->fmt.audio.i_rate == 0 )
        return false;
    date_Init( &p_stream->dts, p_stream->fmt.audio.i_rate, 1 );

    oggpack_adv( &opb, 32 );
    p_stream->fmt.i_bitrate = oggpack_read( &opb, 32 ); /* is signed 32 */
    if( p_stream->fmt.i_bitrate > INT32_MAX ) p_stream->fmt.i_bitrate = 0;
    return true;
}