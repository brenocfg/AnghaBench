#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  device; scalar_t__ gl_nv_surface; int /*<<< orphan*/  vdp; } ;
typedef  TYPE_1__ vlc_vdp_output_surface_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
typedef  TYPE_2__ video_format_t ;
typedef  int /*<<< orphan*/  vdp_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_11__ {int /*<<< orphan*/  pf_destroy; TYPE_1__* p_sys; } ;
typedef  TYPE_3__ picture_resource_t ;
typedef  scalar_t__ VdpStatus ;
typedef  int /*<<< orphan*/  VdpRGBAFormat ;

/* Variables and functions */
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * picture_NewFromResource (TYPE_2__ const*,TYPE_3__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_hold_x11 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vdp_output_surface_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_output_surface_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vdp_output_surface_destroy ; 

__attribute__((used)) static
picture_t *vlc_vdp_output_surface_create(vdp_t *vdp, VdpRGBAFormat rgb_fmt,
                                         const video_format_t *restrict fmt)
{
    vlc_vdp_output_surface_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return NULL;

    sys->vdp = vdp_hold_x11(vdp, &sys->device);
    sys->gl_nv_surface = 0;

    VdpStatus err = vdp_output_surface_create(vdp, sys->device, rgb_fmt,
        fmt->i_visible_width, fmt->i_visible_height, &sys->surface);
    if (err != VDP_STATUS_OK)
    {
error:
        vdp_release_x11(vdp);
        free(sys);
        return NULL;
    }

    picture_resource_t res = {
        .p_sys = sys,
        .pf_destroy = vlc_vdp_output_surface_destroy,
    };

    picture_t *pic = picture_NewFromResource(fmt, &res);
    if (unlikely(pic == NULL))
    {
        vdp_output_surface_destroy(vdp, sys->surface);
        goto error;
    }
    return pic;
}