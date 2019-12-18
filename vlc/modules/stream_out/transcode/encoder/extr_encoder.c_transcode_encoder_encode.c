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
struct TYPE_10__ {TYPE_2__* p_encoder; } ;
typedef  TYPE_3__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_8__ {int i_cat; } ;
struct TYPE_9__ {TYPE_1__ fmt_in; } ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/ * transcode_encoder_audio_encode (TYPE_3__*,void*) ; 
 int /*<<< orphan*/ * transcode_encoder_spu_encode (TYPE_3__*,void*) ; 
 int /*<<< orphan*/ * transcode_encoder_video_encode (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

block_t * transcode_encoder_encode( transcode_encoder_t *p_enc, void *in )
{
    switch( p_enc->p_encoder->fmt_in.i_cat )
    {
        case VIDEO_ES:
            return transcode_encoder_video_encode( p_enc, in );
        case AUDIO_ES:
            return transcode_encoder_audio_encode( p_enc, in );
        case SPU_ES:
            return transcode_encoder_spu_encode( p_enc, in );
        default:
            vlc_assert_unreachable();
            return NULL;
    }
}