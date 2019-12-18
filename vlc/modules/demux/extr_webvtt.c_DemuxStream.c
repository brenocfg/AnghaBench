#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_streamparser; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  webvtt_text_parser_Feed (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int DemuxStream( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    char *psz_line = vlc_stream_ReadLine( p_demux->s );
    webvtt_text_parser_Feed( p_sys->p_streamparser, psz_line );

    return ( psz_line == NULL ) ? VLC_DEMUXER_EOF : VLC_DEMUXER_SUCCESS;
}