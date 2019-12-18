#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_12__ {scalar_t__ i_codec; scalar_t__ i_original_fourcc; TYPE_3__ audio; } ;
struct TYPE_10__ {scalar_t__ i_codec; } ;
struct TYPE_13__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_4__ fmt_in; TYPE_2__ fmt_out; int /*<<< orphan*/  pf_packetize; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_9__ {scalar_t__ buf_size; } ;
struct TYPE_14__ {int b_packetizer; int b_has_headers; scalar_t__ i_frame_in_packet; int /*<<< orphan*/ * p_header; int /*<<< orphan*/ * p_state; int /*<<< orphan*/  end_date; int /*<<< orphan*/  rtp_rate; TYPE_1__ bits; } ;
typedef  TYPE_6__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeAudio ; 
 int /*<<< orphan*/  DecodeRtpSpeexPacket ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Packetize ; 
 scalar_t__ VLC_CODEC_S16N ; 
 scalar_t__ VLC_CODEC_SPEEX ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int OpenCommon( vlc_object_t *p_this, bool b_packetizer )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_SPEEX )
        return VLC_EGENERIC;

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_dec->p_sys = p_sys = malloc(sizeof(decoder_sys_t)) ) == NULL )
        return VLC_ENOMEM;
    p_sys->bits.buf_size = 0;
    p_sys->b_packetizer = b_packetizer;
    p_sys->rtp_rate = p_dec->fmt_in.audio.i_rate;
    p_sys->b_has_headers = false;

    date_Set( &p_sys->end_date, VLC_TICK_INVALID );

    if( b_packetizer )
    {
        p_dec->fmt_out.i_codec = VLC_CODEC_SPEEX;
        p_dec->pf_packetize    = Packetize;
    }
    else
    {
        /* Set output properties */
        p_dec->fmt_out.i_codec = VLC_CODEC_S16N;

        /*
          Set callbacks
          If the codec is spxr then this decoder is
          being invoked on a Speex stream arriving via RTP.
          A special decoder callback is used.
        */
        if (p_dec->fmt_in.i_original_fourcc == VLC_FOURCC('s', 'p', 'x', 'r'))
        {
            msg_Dbg( p_dec, "Using RTP version of Speex decoder @ rate %d.",
            p_dec->fmt_in.audio.i_rate );
            p_dec->pf_decode = DecodeRtpSpeexPacket;
        }
        else
        {
            p_dec->pf_decode = DecodeAudio;
        }
    }
    p_dec->pf_flush        = Flush;

    p_sys->p_state = NULL;
    p_sys->p_header = NULL;
    p_sys->i_frame_in_packet = 0;

    return VLC_SUCCESS;
}