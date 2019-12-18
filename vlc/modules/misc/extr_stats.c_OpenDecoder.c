#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int i_width; int i_height; int i_sar_num; int i_sar_den; } ;
struct TYPE_4__ {TYPE_2__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_6__ {TYPE_1__ fmt_out; int /*<<< orphan*/  pf_decode; } ;
typedef  TYPE_3__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int OpenDecoder ( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;

    msg_Dbg( p_this, "opening stats decoder" );

    /* Set callbacks */
    p_dec->pf_decode = DecodeBlock;

    /* */
    p_dec->fmt_out.i_codec = VLC_CODEC_I420;
    p_dec->fmt_out.video.i_width = 100;
    p_dec->fmt_out.video.i_height = 100;
    p_dec->fmt_out.video.i_sar_num = 1;
    p_dec->fmt_out.video.i_sar_den = 1;

    return VLC_SUCCESS;
}