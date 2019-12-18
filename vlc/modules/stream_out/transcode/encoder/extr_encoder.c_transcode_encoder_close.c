#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* p_encoder; } ;
typedef  TYPE_2__ transcode_encoder_t ;
struct TYPE_6__ {int i_cat; } ;
struct TYPE_8__ {int /*<<< orphan*/ * p_module; TYPE_1__ fmt_in; } ;

/* Variables and functions */
#define  VIDEO_ES 128 
 int /*<<< orphan*/  module_unneed (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transcode_encoder_video_close (TYPE_2__*) ; 

void transcode_encoder_close( transcode_encoder_t *p_enc )
{
    if( !p_enc->p_encoder->p_module )
        return;

    switch( p_enc->p_encoder->fmt_in.i_cat )
    {
        case VIDEO_ES:
            transcode_encoder_video_close( p_enc );
            break;
        default:
            module_unneed( p_enc->p_encoder, p_enc->p_encoder->p_module );
            break;
    }

    p_enc->p_encoder->p_module = NULL;
}