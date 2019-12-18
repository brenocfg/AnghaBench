#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_6__* p_encoder; } ;
typedef  TYPE_2__ transcode_encoder_t ;
struct TYPE_9__ {int /*<<< orphan*/  psz_name; int /*<<< orphan*/  i_codec; int /*<<< orphan*/  p_config_chain; } ;
typedef  TYPE_3__ transcode_encoder_config_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_10__ {scalar_t__ p_module; TYPE_1__ fmt_out; int /*<<< orphan*/  p_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ module_need (TYPE_6__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_fourcc_GetCodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int transcode_encoder_audio_open( transcode_encoder_t *p_enc,
                                  const transcode_encoder_config_t *p_cfg )
{
    p_enc->p_encoder->p_cfg = p_cfg->p_config_chain;
    p_enc->p_encoder->fmt_out.i_codec = p_cfg->i_codec;

    p_enc->p_encoder->p_module = module_need( p_enc->p_encoder, "encoder",
                                              p_cfg->psz_name, true );

    if( p_enc->p_encoder->p_module )
    {
        p_enc->p_encoder->fmt_out.i_codec =
                vlc_fourcc_GetCodec( AUDIO_ES, p_enc->p_encoder->fmt_out.i_codec );
    }

    return ( p_enc->p_encoder->p_module ) ? VLC_SUCCESS: VLC_EGENERIC;
}