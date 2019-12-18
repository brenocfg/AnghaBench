#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  private_type; TYPE_1__* ops; scalar_t__ device; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ vlc_video_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (scalar_t__) ; 
 int /*<<< orphan*/  vlc_video_context_GetPrivate (TYPE_2__*,int /*<<< orphan*/ ) ; 

void vlc_video_context_Release(vlc_video_context *vctx)
{
    if ( vlc_atomic_rc_dec( &vctx->rc ) )
    {
        if (vctx->device)
            vlc_decoder_device_Release( vctx->device );
        if ( vctx->ops && vctx->ops->destroy )
            vctx->ops->destroy( vlc_video_context_GetPrivate(vctx, vctx->private_type) );
        free(vctx);
    }
}