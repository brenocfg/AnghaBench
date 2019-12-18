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
struct dmx_region_t {TYPE_2__* picture; int /*<<< orphan*/  resource; int /*<<< orphan*/  element; int /*<<< orphan*/  bmp_rect; } ;
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_pixels; int /*<<< orphan*/  i_pitch; } ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_IMAGE_RGBA32 ; 
 int /*<<< orphan*/  vc_dispmanx_element_change_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmx_region_update(struct dmx_region_t *dmx_region,
                DISPMANX_UPDATE_HANDLE_T update, picture_t *picture)
{
    vc_dispmanx_resource_write_data(dmx_region->resource, VC_IMAGE_RGBA32,
                    picture->p[0].i_pitch, picture->p[0].p_pixels, &dmx_region->bmp_rect);
    vc_dispmanx_element_change_source(update, dmx_region->element, dmx_region->resource);
    dmx_region->picture = picture;
}