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
struct TYPE_9__ {scalar_t__ i_headers_flags; scalar_t__ p_comment; scalar_t__ p_info; } ;
struct TYPE_8__ {TYPE_3__ vorbis; } ;
struct TYPE_7__ {scalar_t__ i_codec; } ;
struct TYPE_10__ {TYPE_2__ special; TYPE_1__ fmt; } ;
typedef  TYPE_4__ logical_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (scalar_t__) ; 
 scalar_t__ VLC_CODEC_VORBIS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_4__*) ; 
 int /*<<< orphan*/  vorbis_comment_clear (scalar_t__) ; 
 int /*<<< orphan*/  vorbis_info_clear (scalar_t__) ; 

__attribute__((used)) static void Ogg_CleanSpecificData( logical_stream_t *p_stream )
{
#ifdef HAVE_LIBVORBIS
    if ( p_stream->fmt.i_codec == VLC_CODEC_VORBIS )
    {
        if( p_stream->special.vorbis.p_info )
            vorbis_info_clear( p_stream->special.vorbis.p_info );
        FREENULL( p_stream->special.vorbis.p_info );
        if( p_stream->special.vorbis.p_comment )
            vorbis_comment_clear( p_stream->special.vorbis.p_comment );
        FREENULL( p_stream->special.vorbis.p_comment );
        p_stream->special.vorbis.i_headers_flags = 0;
    }
#else
    VLC_UNUSED( p_stream );
#endif
}