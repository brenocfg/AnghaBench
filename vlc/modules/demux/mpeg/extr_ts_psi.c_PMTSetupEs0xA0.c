#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* i_height; void* i_visible_height; void* i_width; void* i_visible_width; } ;
struct TYPE_10__ {scalar_t__ i_extra; int b_packetized; scalar_t__ p_extra; TYPE_1__ video; } ;
struct TYPE_9__ {TYPE_3__ fmt; } ;
typedef  TYPE_2__ ts_es_t ;
typedef  TYPE_3__ es_format_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_11__ {int i_length; int /*<<< orphan*/ * p_data; } ;
typedef  TYPE_4__ dvbpsi_descriptor_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 void* GetWBE (int /*<<< orphan*/ *) ; 
 TYPE_4__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_FOURCC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void PMTSetupEs0xA0( demux_t *p_demux, ts_es_t *p_es,
                           const dvbpsi_pmt_es_t *p_dvbpsies )
{
    /* MSCODEC sent by vlc */
    dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0xa0 );
    if( !p_dr || p_dr->i_length < 10 )
    {
        msg_Warn( p_demux,
                  "private MSCODEC (vlc) without bih private descriptor" );
        return;
    }

    es_format_t *p_fmt = &p_es->fmt;
    es_format_Change( &p_es->fmt, VIDEO_ES,
                      VLC_FOURCC( p_dr->p_data[0], p_dr->p_data[1],
                                 p_dr->p_data[2], p_dr->p_data[3] ) );
    p_fmt->video.i_width = GetWBE( &p_dr->p_data[4] );
    p_fmt->video.i_height = GetWBE( &p_dr->p_data[6] );
    p_fmt->video.i_visible_width = p_fmt->video.i_width;
    p_fmt->video.i_visible_height = p_fmt->video.i_height;
    p_fmt->i_extra = GetWBE( &p_dr->p_data[8] );

    if( p_fmt->i_extra > 0 )
    {
        p_fmt->p_extra = malloc( p_fmt->i_extra );
        if( p_fmt->p_extra )
            memcpy( p_fmt->p_extra, &p_dr->p_data[10],
                    __MIN( p_fmt->i_extra, p_dr->i_length - 10 ) );
        else
            p_fmt->i_extra = 0;
    }
    /* For such stream we will gather them ourself and don't launch a
     * packetizer.
     * Yes it's ugly but it's the only way to have DIV3 working */
    p_fmt->b_packetized = true;
}