#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_context; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void EndAudioDec( vlc_object_t *obj )
{
    decoder_t *p_dec = (decoder_t *)obj;
    decoder_sys_t *sys = p_dec->p_sys;
    AVCodecContext *ctx = sys->p_context;

    avcodec_free_context( &ctx );
    free( sys );
}