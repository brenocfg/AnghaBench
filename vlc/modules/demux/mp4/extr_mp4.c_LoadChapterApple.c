#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {scalar_t__ i_time_offset; int /*<<< orphan*/ * psz_name; } ;
typedef  TYPE_2__ seekpoint_t ;
typedef  int /*<<< orphan*/  p_buffer ;
struct TYPE_20__ {scalar_t__ i_sample; scalar_t__ i_sample_count; size_t i_chunk; TYPE_1__* chunk; } ;
typedef  TYPE_3__ mp4_track_t ;
struct TYPE_21__ {int /*<<< orphan*/  s; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_22__ {TYPE_8__* p_title; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_23__ {int /*<<< orphan*/  seekpoint; int /*<<< orphan*/  i_seekpoint; } ;
struct TYPE_18__ {scalar_t__ i_sample_first; scalar_t__ i_sample_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureUTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FromCharset (char*,char const*,scalar_t__ const) ; 
 int GetWBE (char*) ; 
 scalar_t__ MP4_TrackGetDTS (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  MP4_TrackGetPTSDelta (TYPE_4__*,TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  MP4_TrackGetPos (TYPE_3__*) ; 
 scalar_t__ MP4_TrackGetReadSize (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ const __MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ __MIN (int,scalar_t__ const) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 scalar_t__ stream_ReadU32 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * strndup (char const*,scalar_t__ const) ; 
 TYPE_8__* vlc_input_title_New () ; 
 int /*<<< orphan*/  vlc_seekpoint_Delete (TYPE_2__*) ; 
 TYPE_2__* vlc_seekpoint_New () ; 
 int /*<<< orphan*/  vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LoadChapterApple( demux_t  *p_demux, mp4_track_t *tk )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    for( tk->i_sample = 0; tk->i_sample < tk->i_sample_count; tk->i_sample++ )
    {
        const vlc_tick_t i_dts = MP4_TrackGetDTS( p_demux, tk );
        vlc_tick_t i_pts_delta;
        if ( !MP4_TrackGetPTSDelta( p_demux, tk, &i_pts_delta ) )
            i_pts_delta = 0;
        uint32_t i_nb_samples = 0;
        const uint32_t i_size = MP4_TrackGetReadSize( tk, &i_nb_samples );

        if( i_size > 0 && !vlc_stream_Seek( p_demux->s, MP4_TrackGetPos( tk ) ) )
        {
            char p_buffer[256];
            const uint32_t i_read = stream_ReadU32( p_demux->s, p_buffer,
                                                    __MIN( sizeof(p_buffer), i_size ) );
            if( i_read > 2 )
            {
                const uint32_t i_string = __MIN( GetWBE(p_buffer), i_read-2 );
                const char *psnz_string = &p_buffer[2];

                seekpoint_t *s = vlc_seekpoint_New();
                if( s == NULL ) continue;

                if( i_string > 1 && !memcmp( psnz_string, "\xFF\xFE", 2 ) )
                    s->psz_name = FromCharset( "UTF-16LE", psnz_string, i_string );
                else
                    s->psz_name = strndup( psnz_string, i_string );

                if( s->psz_name == NULL )
                {
                    vlc_seekpoint_Delete( s );
                    continue;
                }

                EnsureUTF8( s->psz_name );
                s->i_time_offset = i_dts + __MAX( i_pts_delta, 0 );

                if( !p_sys->p_title )
                    p_sys->p_title = vlc_input_title_New();
                TAB_APPEND( p_sys->p_title->i_seekpoint, p_sys->p_title->seekpoint, s );
            }
        }
        if( tk->i_sample+1 >= tk->chunk[tk->i_chunk].i_sample_first +
                              tk->chunk[tk->i_chunk].i_sample_count )
            tk->i_chunk++;
    }
}