#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_18__ {scalar_t__ layer; int /*<<< orphan*/  dmx_handle; } ;
typedef  TYPE_4__ vout_display_sys_t ;
struct TYPE_19__ {int i_visible_width; int i_visible_height; } ;
typedef  TYPE_5__ video_format_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {TYPE_2__* p_picture; int /*<<< orphan*/  i_alpha; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; TYPE_5__ fmt; } ;
typedef  TYPE_6__ subpicture_region_t ;
struct TYPE_14__ {int flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  opacity; } ;
struct TYPE_21__ {int width; int height; } ;
struct dmx_region_t {TYPE_2__* picture; int /*<<< orphan*/ * next; TYPE_11__ alpha; TYPE_7__ src_rect; int /*<<< orphan*/  resource; TYPE_7__ dst_rect; int /*<<< orphan*/  element; TYPE_7__ bmp_rect; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; } ;
struct TYPE_16__ {TYPE_1__* p; } ;
struct TYPE_15__ {int i_pitch; int /*<<< orphan*/  p_pixels; } ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int DISPMANX_FLAGS_ALPHA_FROM_SOURCE ; 
 int DISPMANX_FLAGS_ALPHA_MIX ; 
 int /*<<< orphan*/  DISPMANX_NO_HANDLE ; 
 int /*<<< orphan*/  DISPMANX_PROTECTION_NONE ; 
 int /*<<< orphan*/  VC_IMAGE_RGBA32 ; 
 int /*<<< orphan*/  VC_IMAGE_ROT0 ; 
 struct dmx_region_t* malloc (int) ; 
 int /*<<< orphan*/  vc_dispmanx_element_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_rect_set (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static struct dmx_region_t *dmx_region_new(vout_display_t *vd,
                DISPMANX_UPDATE_HANDLE_T update, subpicture_region_t *region)
{
    vout_display_sys_t *sys = vd->sys;
    video_format_t *fmt = &region->fmt;
    struct dmx_region_t *dmx_region = malloc(sizeof(struct dmx_region_t));
    uint32_t image_handle;

    dmx_region->pos_x = region->i_x;
    dmx_region->pos_y = region->i_y;

    vc_dispmanx_rect_set(&dmx_region->bmp_rect, 0, 0, fmt->i_visible_width,
                    fmt->i_visible_height);
    vc_dispmanx_rect_set(&dmx_region->src_rect, 0, 0, fmt->i_visible_width << 16,
                    fmt->i_visible_height << 16);
    vc_dispmanx_rect_set(&dmx_region->dst_rect, region->i_x, region->i_y,
                    fmt->i_visible_width, fmt->i_visible_height);

    dmx_region->resource = vc_dispmanx_resource_create(VC_IMAGE_RGBA32,
                    dmx_region->bmp_rect.width | (region->p_picture->p[0].i_pitch << 16),
                    dmx_region->bmp_rect.height | (dmx_region->bmp_rect.height << 16),
                    &image_handle);
    vc_dispmanx_resource_write_data(dmx_region->resource, VC_IMAGE_RGBA32,
                    region->p_picture->p[0].i_pitch,
                    region->p_picture->p[0].p_pixels, &dmx_region->bmp_rect);

    dmx_region->alpha.flags = DISPMANX_FLAGS_ALPHA_FROM_SOURCE | DISPMANX_FLAGS_ALPHA_MIX;
    dmx_region->alpha.opacity = region->i_alpha;
    dmx_region->alpha.mask = DISPMANX_NO_HANDLE;
    dmx_region->element = vc_dispmanx_element_add(update, sys->dmx_handle,
                    sys->layer + 1, &dmx_region->dst_rect, dmx_region->resource,
                    &dmx_region->src_rect, DISPMANX_PROTECTION_NONE,
                    &dmx_region->alpha, NULL, VC_IMAGE_ROT0);

    dmx_region->next = NULL;
    dmx_region->picture = region->p_picture;

    return dmx_region;
}