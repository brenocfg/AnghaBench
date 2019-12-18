#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int b_packetized; scalar_t__ i_codec; } ;
struct TYPE_11__ {scalar_t__ i_codec; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; TYPE_5__ fmt_out; TYPE_6__ fmt_in; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_pts; } ;
struct TYPE_9__ {int b_stream_info; int /*<<< orphan*/  pts; int /*<<< orphan*/  bytestream; scalar_t__ i_next_block_flags; int /*<<< orphan*/ * p_buf; scalar_t__ i_buf; TYPE_1__ headerinfo; scalar_t__ i_frame_size; int /*<<< orphan*/  i_last_frame_size; scalar_t__ i_offset; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC_FRAME_SIZE_MIN ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Packetize ; 
 int /*<<< orphan*/  STATE_NOSYNC ; 
 scalar_t__ VLC_CODEC_FLAC ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_BytestreamInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_5__*,TYPE_6__*) ; 
 TYPE_3__* malloc (int) ; 

__attribute__((used)) static int Open(vlc_object_t *p_this)
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if (p_dec->fmt_in.i_codec != VLC_CODEC_FLAC)
        return VLC_EGENERIC;


    /* */
    p_dec->p_sys = p_sys = malloc(sizeof(*p_sys));
    if (!p_sys)
        return VLC_ENOMEM;

    p_sys->i_state       = STATE_NOSYNC;
    p_sys->i_offset      = 0;
    p_sys->b_stream_info = false;
    p_sys->i_last_frame_size = FLAC_FRAME_SIZE_MIN;
    p_sys->i_frame_size  = 0;
    p_sys->headerinfo.i_pts  = VLC_TICK_INVALID;
    p_sys->i_buf         = 0;
    p_sys->p_buf         = NULL;
    p_sys->i_next_block_flags = 0;
    block_BytestreamInit(&p_sys->bytestream);
    date_Init( &p_sys->pts, 1, 1 );

    /* */
    es_format_Copy(&p_dec->fmt_out, &p_dec->fmt_in);
    p_dec->fmt_out.i_codec = VLC_CODEC_FLAC;
    p_dec->fmt_out.b_packetized = true;

    /* */
    p_dec->pf_packetize = Packetize;
    p_dec->pf_flush     = Flush;
    p_dec->pf_get_cc    = NULL;

    return VLC_SUCCESS;
}