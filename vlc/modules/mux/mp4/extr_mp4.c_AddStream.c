#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_26__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_mux_t ;
struct TYPE_27__ {int /*<<< orphan*/  pp_streams; scalar_t__ i_nb_streams; int /*<<< orphan*/  muxh; } ;
typedef  TYPE_4__ sout_mux_sys_t ;
struct TYPE_28__ {TYPE_6__* p_sys; TYPE_12__* p_fmt; } ;
typedef  TYPE_5__ sout_input_t ;
struct TYPE_29__ {int /*<<< orphan*/  extrabuilder; int /*<<< orphan*/  tinfo; } ;
typedef  TYPE_6__ mp4_stream_t ;
struct TYPE_25__ {int i_frame_rate; int i_frame_rate_base; } ;
struct TYPE_24__ {int i_rate; } ;
struct TYPE_30__ {TYPE_2__ video; TYPE_1__ audio; } ;
typedef  TYPE_7__ es_format_t ;
struct TYPE_23__ {int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; } ;

/* Variables and functions */
#define  AUDIO_ES 129 
 int /*<<< orphan*/  BRAND_isom ; 
 int /*<<< orphan*/  BRAND_qt__ ; 
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  EXTRADATA_ISOBMFF ; 
 int /*<<< orphan*/  FRAGMENTED ; 
 int /*<<< orphan*/  QUICKTIME ; 
 int /*<<< orphan*/  TAB_APPEND (scalar_t__,int /*<<< orphan*/ ,TYPE_6__*) ; 
#define  VIDEO_ES 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_7__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_7__*,TYPE_12__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 TYPE_6__* mp4_stream_New () ; 
 int /*<<< orphan*/  mp4mux_CanMux (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mp4mux_Is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4mux_track_Add (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mux_extradata_builder_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AddStream(sout_mux_t *p_mux, sout_input_t *p_input)
{
    sout_mux_sys_t  *p_sys = p_mux->p_sys;
    mp4_stream_t    *p_stream;

    if(!mp4mux_CanMux(VLC_OBJECT(p_mux), p_input->p_fmt,
                      mp4mux_Is(p_sys->muxh, QUICKTIME) ? BRAND_qt__ : BRAND_isom,
                      mp4mux_Is(p_sys->muxh, FRAGMENTED)))
    {
        msg_Err(p_mux, "unsupported codec %4.4s in mp4",
                 (char*)&p_input->p_fmt->i_codec);
        return VLC_EGENERIC;
    }

    if(!(p_stream = mp4_stream_New()))
        return VLC_ENOMEM;

    uint32_t i_track_timescale = CLOCK_FREQ;
    es_format_t trackfmt;
    es_format_Init(&trackfmt, p_input->p_fmt->i_cat, p_input->p_fmt->i_codec);
    es_format_Copy(&trackfmt, p_input->p_fmt);

    switch( p_input->p_fmt->i_cat )
    {
    case AUDIO_ES:
        if(!trackfmt.audio.i_rate)
        {
            msg_Warn( p_mux, "no audio rate given for stream %d, assuming 48KHz",
                      p_sys->i_nb_streams );
            trackfmt.audio.i_rate = 48000;
        }
        i_track_timescale = trackfmt.audio.i_rate;
        break;
    case VIDEO_ES:
        if( !trackfmt.video.i_frame_rate ||
            !trackfmt.video.i_frame_rate_base )
        {
            msg_Warn( p_mux, "Missing frame rate for stream %d, assuming 25fps",
                      p_sys->i_nb_streams );
            trackfmt.video.i_frame_rate = 25;
            trackfmt.video.i_frame_rate_base = 1;
        }

        i_track_timescale = trackfmt.video.i_frame_rate *
                            trackfmt.video.i_frame_rate_base;

        if( i_track_timescale > CLOCK_FREQ )
            i_track_timescale = CLOCK_FREQ;
        else if( i_track_timescale < 90000 )
            i_track_timescale = 90000;
        break;
    default:
        break;
    }

    p_stream->tinfo = mp4mux_track_Add(p_sys->muxh, p_sys->i_nb_streams + 1,
                                       &trackfmt, i_track_timescale);
    es_format_Clean(&trackfmt);
    if(!p_stream->tinfo)
    {
        free(p_stream);
        return VLC_ENOMEM;
    }

    p_stream->extrabuilder = mux_extradata_builder_New(p_input->p_fmt->i_codec,
                                                       EXTRADATA_ISOBMFF);

    p_input->p_sys          = p_stream;

    msg_Dbg(p_mux, "adding input");

    TAB_APPEND(p_sys->i_nb_streams, p_sys->pp_streams, p_stream);
    return VLC_SUCCESS;
}