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
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ p_va; int /*<<< orphan*/  cc; int /*<<< orphan*/ * p_context; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 scalar_t__ avcodec_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_va_Delete (scalar_t__) ; 

void EndVideoDec( vlc_object_t *obj )
{
    decoder_t *p_dec = (decoder_t *)obj;
    decoder_sys_t *p_sys = p_dec->p_sys;
    AVCodecContext *ctx = p_sys->p_context;

    /* do not flush buffers if codec hasn't been opened (theora/vorbis/VC1) */
    if( avcodec_is_open( ctx ) )
        avcodec_flush_buffers( ctx );

    cc_Flush( &p_sys->cc );

    avcodec_free_context( &ctx );

    if( p_sys->p_va )
        vlc_va_Delete( p_sys->p_va );

    vlc_mutex_destroy( &p_sys->lock );
    free( p_sys );
}