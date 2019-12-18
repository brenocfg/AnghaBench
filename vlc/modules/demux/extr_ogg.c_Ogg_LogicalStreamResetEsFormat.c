#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i_codec; int /*<<< orphan*/  b_packetized; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; } ;
struct TYPE_7__ {TYPE_3__ fmt; TYPE_4__ fmt_old; } ;
typedef  TYPE_1__ logical_stream_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int Ogg_IsOpusFormatCompatible (TYPE_3__*,TYPE_4__*) ; 
 int Ogg_IsVorbisFormatCompatible (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ VLC_CODEC_FLAC ; 
 scalar_t__ VLC_CODEC_OPUS ; 
 scalar_t__ VLC_CODEC_VORBIS ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool Ogg_LogicalStreamResetEsFormat( demux_t *p_demux, logical_stream_t *p_stream )
{
    bool b_compatible = false;
    if( !p_stream->fmt_old.i_cat || !p_stream->fmt_old.i_codec )
        return true;

    /* Only Vorbis and Opus are supported. */
    if( p_stream->fmt.i_codec == VLC_CODEC_VORBIS )
        b_compatible = Ogg_IsVorbisFormatCompatible( &p_stream->fmt, &p_stream->fmt_old );
    else if( p_stream->fmt.i_codec == VLC_CODEC_OPUS )
        b_compatible = Ogg_IsOpusFormatCompatible( &p_stream->fmt, &p_stream->fmt_old );
    else if( p_stream->fmt.i_codec == VLC_CODEC_FLAC )
        b_compatible = !p_stream->fmt.b_packetized;

    if( !b_compatible )
        msg_Warn( p_demux, "cannot reuse old stream, resetting the decoder" );

    return !b_compatible;
}