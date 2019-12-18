#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_vdp_video_field_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vlc_va_t ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  type; int /*<<< orphan*/  device; int /*<<< orphan*/  vctx; } ;
typedef  TYPE_2__ vlc_va_sys_t ;
struct video_context_private {int /*<<< orphan*/  vdp; } ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
typedef  scalar_t__ VdpStatus ;

/* Variables and functions */
 struct video_context_private* GetVDPAUContextPrivate (int /*<<< orphan*/ ) ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vdp_video_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_video_surface_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_vdp_video_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_vdp_video_field_t *CreateSurface(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;
    struct video_context_private *vctx_priv = GetVDPAUContextPrivate(sys->vctx);
    VdpVideoSurface surface;
    VdpStatus err;

    err = vdp_video_surface_create(vctx_priv->vdp, sys->device, sys->type,
                                   sys->width, sys->height, &surface);
    if (err != VDP_STATUS_OK)
    {
        msg_Err(va, "%s creation failure: %s", "video surface",
                vdp_get_error_string(vctx_priv->vdp, err));
        return NULL;
    }

    vlc_vdp_video_field_t *field = vlc_vdp_video_create(vctx_priv->vdp, surface);
    if (unlikely(field == NULL))
        vdp_video_surface_destroy(vctx_priv->vdp, surface);
    return field;
}