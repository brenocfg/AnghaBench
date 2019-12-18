#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int vlc_fourcc_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_bitspersample; } ;
struct TYPE_13__ {scalar_t__ i_cat; int i_codec; TYPE_1__ audio; } ;
struct TYPE_12__ {int i_codec; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; TYPE_8__ fmt_in; TYPE_7__ fmt_out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pf_parse; int /*<<< orphan*/ * p_block; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Packetize ; 
 int /*<<< orphan*/  PacketizeSub ; 
 int /*<<< orphan*/ * ParseWMV3 ; 
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
#define  VLC_CODEC_WMV3 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_fourcc_GetCodecAudio (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_cat != AUDIO_ES &&
        p_dec->fmt_in.i_cat != VIDEO_ES &&
        p_dec->fmt_in.i_cat != SPU_ES )
    {
        msg_Err( p_dec, "invalid ES type" );
        return VLC_EGENERIC;
    }

    p_dec->p_sys = p_sys = malloc( sizeof(*p_sys) );
    if (unlikely(p_sys == NULL))
        return VLC_ENOMEM;

    p_sys->p_block    = NULL;
    switch( p_dec->fmt_in.i_codec )
    {
    case VLC_CODEC_WMV3:
        p_sys->pf_parse = ParseWMV3;
        break;
    default:
        p_sys->pf_parse = NULL;
        break;
    }

    vlc_fourcc_t fcc = p_dec->fmt_in.i_codec;
    /* Fix the value of the fourcc for audio */
    if( p_dec->fmt_in.i_cat == AUDIO_ES )
    {
        fcc = vlc_fourcc_GetCodecAudio( p_dec->fmt_in.i_codec,
                                                     p_dec->fmt_in.audio.i_bitspersample );
        if( !fcc )
        {
            msg_Err( p_dec, "unknown raw audio sample size" );
            free( p_sys );
            return VLC_EGENERIC;
        }
    }

    /* Create the output format */
    es_format_Copy( &p_dec->fmt_out, &p_dec->fmt_in );
    p_dec->fmt_out.i_codec = fcc;
    if( p_dec->fmt_in.i_cat == SPU_ES )
        p_dec->pf_packetize = PacketizeSub;
    else
        p_dec->pf_packetize = Packetize;
    p_dec->pf_flush = Flush;
    p_dec->pf_get_cc = NULL;

    return VLC_SUCCESS;
}