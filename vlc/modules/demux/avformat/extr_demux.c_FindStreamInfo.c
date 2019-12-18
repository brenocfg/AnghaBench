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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {TYPE_4__* ic; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {unsigned int nb_streams; } ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int /*<<< orphan*/  FreeUnclaimedOptions (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int avformat_find_stream_info (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_avcodec_lock () ; 
 int /*<<< orphan*/  vlc_avcodec_unlock () ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FindStreamInfo( demux_t *p_demux, AVDictionary *options )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    unsigned nb_streams = p_sys->ic->nb_streams;

    AVDictionary *streamsoptions[nb_streams ? nb_streams : 1];

    streamsoptions[0] = options;
    for ( unsigned i = 1; i < nb_streams; i++ )
    {
        streamsoptions[i] = NULL;
        if( streamsoptions[0] )
            av_dict_copy( &streamsoptions[i], streamsoptions[0], 0 );
    }

    vlc_avcodec_lock(); /* avformat calls avcodec behind our back!!! */
    int error = avformat_find_stream_info( p_sys->ic, streamsoptions );
    vlc_avcodec_unlock();

    FreeUnclaimedOptions( p_demux, &streamsoptions[0] );
    for ( unsigned i = 1; i < nb_streams; i++ ) {
        av_dict_free( &streamsoptions[i] );
    }

    if( error < 0 )
    {
        msg_Warn( p_demux, "Could not find stream info: %s",
                  vlc_strerror_c(AVUNERROR(error)) );
    }
}