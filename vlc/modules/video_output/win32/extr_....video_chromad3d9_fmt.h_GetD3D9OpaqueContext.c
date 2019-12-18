#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_video_context ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/ * opaque; } ;
typedef  TYPE_1__ vlc_decoder_device ;
typedef  int /*<<< orphan*/  d3d9_decoder_device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetD3D9OpaqueDevice (TYPE_1__*) ; 
 scalar_t__ VLC_DECODER_DEVICE_DXVA2 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (TYPE_1__*) ; 
 TYPE_1__* vlc_video_context_HoldDevice (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline d3d9_decoder_device_t *GetD3D9OpaqueContext(vlc_video_context *vctx)
{
    vlc_decoder_device *device = vctx ? vlc_video_context_HoldDevice(vctx) : NULL;
    if (unlikely(device == NULL))
        return NULL;
    d3d9_decoder_device_t *res = NULL;
    if (device->type == VLC_DECODER_DEVICE_DXVA2)
    {
        assert(device->opaque != NULL);
        res = GetD3D9OpaqueDevice(device);
    }
    vlc_decoder_device_Release(device);
    return res;
}