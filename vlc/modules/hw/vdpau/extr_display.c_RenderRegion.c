#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_22__ {int width; int height; int /*<<< orphan*/  vdp; int /*<<< orphan*/  device; } ;
typedef  TYPE_4__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_23__ {int i_original_picture_width; int i_original_picture_height; float i_alpha; } ;
typedef  TYPE_5__ subpicture_t ;
struct TYPE_20__ {int i_visible_width; int i_visible_height; } ;
struct TYPE_24__ {int i_x; int i_y; float i_alpha; TYPE_2__ fmt; TYPE_7__* p_picture; } ;
typedef  TYPE_6__ subpicture_region_t ;
struct TYPE_25__ {TYPE_1__* p; } ;
typedef  TYPE_7__ picture_t ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_26__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_8__ VdpRect ;
typedef  int /*<<< orphan*/  VdpRGBAFormat ;
struct TYPE_27__ {int /*<<< orphan*/  blend_constant; int /*<<< orphan*/  blend_equation_alpha; int /*<<< orphan*/  blend_equation_color; int /*<<< orphan*/  blend_factor_destination_alpha; int /*<<< orphan*/  blend_factor_source_alpha; int /*<<< orphan*/  blend_factor_destination_color; int /*<<< orphan*/  blend_factor_source_color; int /*<<< orphan*/  struct_version; } ;
typedef  TYPE_9__ VdpOutputSurfaceRenderBlendState ;
typedef  int /*<<< orphan*/  VdpOutputSurface ;
struct TYPE_18__ {float member_0; float member_1; float member_2; float member_3; } ;
typedef  TYPE_10__ VdpColor ;
typedef  int /*<<< orphan*/  VdpBitmapSurface ;
struct TYPE_19__ {void* p_pixels; int /*<<< orphan*/  i_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_FALSE ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_ADD ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_SRC_ALPHA ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ZERO ; 
 int /*<<< orphan*/  VDP_OUTPUT_SURFACE_RENDER_BLEND_STATE_VERSION ; 
 int /*<<< orphan*/  VDP_RGBA_FORMAT_B8G8R8A8 ; 
 int /*<<< orphan*/  VDP_RGBA_FORMAT_R8G8B8A8 ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,char*,...) ; 
 scalar_t__ vdp_bitmap_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_bitmap_surface_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vdp_bitmap_surface_put_bits_native (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vdp_output_surface_render_bitmap_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void RenderRegion(vout_display_t *vd, VdpOutputSurface target,
                         const subpicture_t *subpic,
                         const subpicture_region_t *reg)
{
    vout_display_sys_t *sys = vd->sys;
    VdpBitmapSurface surface;
#ifdef WORDS_BIGENDIAN
    VdpRGBAFormat fmt = VDP_RGBA_FORMAT_B8G8R8A8;
#else
    VdpRGBAFormat fmt = VDP_RGBA_FORMAT_R8G8B8A8;
#endif
    VdpStatus err;

    /* Create GPU surface for sub-picture */
    err = vdp_bitmap_surface_create(sys->vdp, sys->device, fmt,
        reg->fmt.i_visible_width, reg->fmt.i_visible_height, VDP_FALSE,
                                    &surface);
    if (err != VDP_STATUS_OK)
    {
        msg_Err(vd, "%s creation failure: %s", "bitmap surface",
                vdp_get_error_string(sys->vdp, err));
        return;
    }

    /* Upload sub-picture to GPU surface */
    picture_t *pic = reg->p_picture;
    const void *data = pic->p[0].p_pixels;
    uint32_t pitch = pic->p[0].i_pitch;

    err = vdp_bitmap_surface_put_bits_native(sys->vdp, surface, &data, &pitch,
                                             NULL);
    if (err != VDP_STATUS_OK)
    {
        msg_Err(vd, "subpicture upload failure: %s",
                vdp_get_error_string(sys->vdp, err));
        goto out;
    }

    /* Render onto main surface */
    VdpRect area = {
        reg->i_x * sys->width
            / subpic->i_original_picture_width,
        reg->i_y * sys->height
            / subpic->i_original_picture_height,
        (reg->i_x + reg->fmt.i_visible_width) * sys->width
            / subpic->i_original_picture_width,
        (reg->i_y + reg->fmt.i_visible_height) * sys->height
            / subpic->i_original_picture_height,
    };
    VdpColor color = { 1.f, 1.f, 1.f,
        reg->i_alpha * subpic->i_alpha / 65025.f };
    VdpOutputSurfaceRenderBlendState state = {
        .struct_version = VDP_OUTPUT_SURFACE_RENDER_BLEND_STATE_VERSION,
        .blend_factor_source_color =
            VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_SRC_ALPHA,
        .blend_factor_destination_color =
            VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .blend_factor_source_alpha =
            VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ZERO,
        .blend_factor_destination_alpha =
            VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE,
        .blend_equation_color = VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_ADD,
        .blend_equation_alpha = VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_ADD,
        .blend_constant = { 0.f, 0.f, 0.f, 0.f },
    };

    err = vdp_output_surface_render_bitmap_surface(sys->vdp, target, &area,
                                             surface, NULL, &color, &state, 0);
    if (err != VDP_STATUS_OK)
        msg_Err(vd, "blending failure: %s",
                vdp_get_error_string(sys->vdp, err));

out:/* Destroy GPU surface */
    vdp_bitmap_surface_destroy(sys->vdp, surface);
}