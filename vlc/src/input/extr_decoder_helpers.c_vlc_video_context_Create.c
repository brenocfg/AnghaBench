#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int private_type; size_t private_size; struct vlc_video_context_operations const* ops; int /*<<< orphan*/ * device; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ vlc_video_context ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
struct vlc_video_context_operations {int dummy; } ;
typedef  enum vlc_video_context_type { ____Placeholder_vlc_video_context_type } vlc_video_context_type ;

/* Variables and functions */
 int VLC_VIDEO_CONTEXT_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_decoder_device_Hold (int /*<<< orphan*/ *) ; 

vlc_video_context * vlc_video_context_Create(vlc_decoder_device *device,
                                          enum vlc_video_context_type private_type,
                                          size_t private_size,
                                          const struct vlc_video_context_operations *ops)
{
    assert(private_type != VLC_VIDEO_CONTEXT_NONE); // use a NULL video context for that
    vlc_video_context *vctx = malloc(sizeof(*vctx) + private_size);
    if (unlikely(vctx == NULL))
        return NULL;
    vlc_atomic_rc_init( &vctx->rc );
    vctx->private_type = private_type;
    vctx->private_size = private_size;
    vctx->device = device;
    if (vctx->device)
        vlc_decoder_device_Hold( vctx->device );
    vctx->ops = ops;
    return vctx;
}