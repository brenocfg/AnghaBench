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
typedef  int uint64_t ;
struct TYPE_8__ {int bytes; int /*<<< orphan*/ * packet; } ;
typedef  TYPE_2__ ogg_packet ;
struct TYPE_7__ {int /*<<< orphan*/  i_frame_rate_base; int /*<<< orphan*/  i_frame_rate; } ;
struct TYPE_10__ {TYPE_1__ video; } ;
struct TYPE_9__ {int b_force_backup; int /*<<< orphan*/  i_granule_shift; TYPE_4__ fmt; int /*<<< orphan*/  dts; } ;
typedef  TYPE_3__ logical_stream_t ;

/* Variables and functions */
 int GetQWLE (int /*<<< orphan*/ *) ; 
 int GetWLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_OGGSPOTS ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ureduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Ogg_ReadOggSpotsHeader( logical_stream_t *p_stream,
                                    ogg_packet *p_oggpacket )
{
    uint64_t i_granulerate_numerator;
    uint64_t i_granulerate_denominator;
    int i_major;
    int i_minor;

    es_format_Change( &p_stream->fmt, VIDEO_ES, VLC_CODEC_OGGSPOTS );

    /* Signal that we want to keep a backup of the OggSpots
     * stream headers. They will be used when switching between
     * audio streams. */
    p_stream->b_force_backup = true;

    /* Cheat and get additionnal info ;) */
    if ( p_oggpacket->bytes != 52 )
    {
        /* The OggSpots header is always 52 bytes */
        return false;
    }

    i_major = GetWLE( &p_oggpacket->packet[ 8] ); /* major version num */
    i_minor = GetWLE( &p_oggpacket->packet[10] ); /* minor version num */
    if ( i_major != 0 || i_minor != 1 )
    {
        return false;
    }

    /* Granule rate */
    i_granulerate_numerator   = GetQWLE( &p_oggpacket->packet[12] );
    i_granulerate_denominator = GetQWLE( &p_oggpacket->packet[20] );
    if ( i_granulerate_numerator == 0 || i_granulerate_denominator == 0 )
    {
        return false;
    }

    /* The OggSpots spec contained an error and there are implementations out
     * there that used the wrong value. So we detect that case and switch
     * numerator and denominator in that case */
    if ( i_granulerate_numerator == 1 && i_granulerate_denominator == 30 )
    {
        i_granulerate_numerator   = 30;
        i_granulerate_denominator = 1;
    }

    if ( !i_granulerate_numerator || !i_granulerate_denominator )
        return false;

    /* Normalize granulerate */
    vlc_ureduce(&p_stream->fmt.video.i_frame_rate,
                &p_stream->fmt.video.i_frame_rate_base,
                i_granulerate_numerator, i_granulerate_denominator, 0);

    date_Init( &p_stream->dts, p_stream->fmt.video.i_frame_rate,
                               p_stream->fmt.video.i_frame_rate_base );

    p_stream->i_granule_shift = p_oggpacket->packet[28];

    return true;
}