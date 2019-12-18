#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {scalar_t__ i_track; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ i_stream; scalar_t__ i_cat; int i_fourcc; } ;
typedef  TYPE_3__ avi_packet_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
#define  AVIFOURCC_JUNK 131 
#define  AVIFOURCC_LIST 130 
#define  AVIFOURCC_RIFF 129 
#define  AVIFOURCC_idx1 128 
 int /*<<< orphan*/  AVI_PacketGetHeader (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int AVI_PacketSearch( demux_t *p_demux )
{
    demux_sys_t     *p_sys = p_demux->p_sys;
    avi_packet_t    avi_pk;
    unsigned short  i_count = 0;

    for( ;; )
    {
        if( vlc_stream_Read( p_demux->s, NULL, 1 ) != 1 )
        {
            return VLC_EGENERIC;
        }
        AVI_PacketGetHeader( p_demux, &avi_pk );
        if( avi_pk.i_stream < p_sys->i_track &&
            ( avi_pk.i_cat == AUDIO_ES || avi_pk.i_cat == VIDEO_ES ) )
        {
            return VLC_SUCCESS;
        }
        switch( avi_pk.i_fourcc )
        {
            case AVIFOURCC_JUNK:
            case AVIFOURCC_LIST:
            case AVIFOURCC_RIFF:
            case AVIFOURCC_idx1:
                return VLC_SUCCESS;
        }

        if( !++i_count )
            msg_Warn( p_demux, "trying to resync..." );
    }
}