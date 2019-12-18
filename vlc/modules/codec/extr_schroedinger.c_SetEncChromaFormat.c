#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int i_bits_per_pixel; } ;
struct TYPE_8__ {int i_codec; TYPE_1__ video; } ;
struct TYPE_10__ {TYPE_2__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ encoder_t ;
struct TYPE_11__ {TYPE_3__* p_format; } ;
typedef  TYPE_5__ encoder_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  chroma_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHRO_CHROMA_420 ; 
 int /*<<< orphan*/  SCHRO_CHROMA_422 ; 
 int /*<<< orphan*/  SCHRO_CHROMA_444 ; 
#define  VLC_CODEC_I420 130 
#define  VLC_CODEC_I422 129 
#define  VLC_CODEC_I444 128 

__attribute__((used)) static bool SetEncChromaFormat( encoder_t *p_enc, uint32_t i_codec )
{
    encoder_sys_t *p_sys = p_enc->p_sys;

    switch( i_codec ) {
    case VLC_CODEC_I420:
        p_enc->fmt_in.i_codec = i_codec;
        p_enc->fmt_in.video.i_bits_per_pixel = 12;
        p_sys->p_format->chroma_format = SCHRO_CHROMA_420;
           break;
    case VLC_CODEC_I422:
        p_enc->fmt_in.i_codec = i_codec;
        p_enc->fmt_in.video.i_bits_per_pixel = 16;
        p_sys->p_format->chroma_format = SCHRO_CHROMA_422;
        break;
    case VLC_CODEC_I444:
        p_enc->fmt_in.i_codec = i_codec;
        p_enc->fmt_in.video.i_bits_per_pixel = 24;
        p_sys->p_format->chroma_format = SCHRO_CHROMA_444;
        break;
    default:
        return false;
    }

    return true;
}