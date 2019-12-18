#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_15__ {struct dmx_region_t* dmx_region; } ;
typedef  TYPE_4__ vout_display_sys_t ;
struct TYPE_16__ {scalar_t__ i_visible_height; scalar_t__ i_visible_width; } ;
typedef  TYPE_5__ video_format_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_17__ {TYPE_7__* p_region; } ;
typedef  TYPE_6__ subpicture_t ;
struct TYPE_18__ {scalar_t__ i_x; scalar_t__ i_y; struct TYPE_18__* p_next; scalar_t__ i_alpha; TYPE_5__ fmt; int /*<<< orphan*/ * p_picture; } ;
typedef  TYPE_7__ subpicture_region_t ;
struct TYPE_13__ {scalar_t__ opacity; } ;
struct TYPE_12__ {scalar_t__ width; scalar_t__ height; } ;
struct dmx_region_t {scalar_t__ pos_x; scalar_t__ pos_y; struct dmx_region_t* next; int /*<<< orphan*/ * picture; TYPE_2__ alpha; TYPE_1__ bmp_rect; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  dmx_region_delete (struct dmx_region_t*,scalar_t__) ; 
 struct dmx_region_t* dmx_region_new (TYPE_3__*,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  dmx_region_update (struct dmx_region_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_dispmanx_update_start (int) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (scalar_t__) ; 

__attribute__((used)) static void display_subpicture(vout_display_t *vd, subpicture_t *subpicture)
{
    vout_display_sys_t *sys = vd->sys;
    struct dmx_region_t **dmx_region = &sys->dmx_region;
    struct dmx_region_t *unused_dmx_region;
    DISPMANX_UPDATE_HANDLE_T update = 0;
    picture_t *picture;
    video_format_t *fmt;
    struct dmx_region_t *dmx_region_next;

    if(subpicture) {
        subpicture_region_t *region = subpicture->p_region;
        while(region) {
            picture = region->p_picture;
            fmt = &region->fmt;

            if(!*dmx_region) {
                if(!update)
                    update = vc_dispmanx_update_start(10);
                *dmx_region = dmx_region_new(vd, update, region);
            } else if(((*dmx_region)->bmp_rect.width != (int32_t)fmt->i_visible_width) ||
                    ((*dmx_region)->bmp_rect.height != (int32_t)fmt->i_visible_height) ||
                    ((*dmx_region)->pos_x != region->i_x) ||
                    ((*dmx_region)->pos_y != region->i_y) ||
                    ((*dmx_region)->alpha.opacity != (uint32_t)region->i_alpha)) {
                dmx_region_next = (*dmx_region)->next;
                if(!update)
                    update = vc_dispmanx_update_start(10);
                dmx_region_delete(*dmx_region, update);
                *dmx_region = dmx_region_new(vd, update, region);
                (*dmx_region)->next = dmx_region_next;
            } else if((*dmx_region)->picture != picture) {
                if(!update)
                    update = vc_dispmanx_update_start(10);
                dmx_region_update(*dmx_region, update, picture);
            }

            dmx_region = &(*dmx_region)->next;
            region = region->p_next;
        }
    }

    /* Remove remaining regions */
    unused_dmx_region = *dmx_region;
    while(unused_dmx_region) {
        dmx_region_next = unused_dmx_region->next;
        if(!update)
            update = vc_dispmanx_update_start(10);
        dmx_region_delete(unused_dmx_region, update);
        unused_dmx_region = dmx_region_next;
    }
    *dmx_region = NULL;

    if(update)
        vc_dispmanx_update_submit_sync(update);
}