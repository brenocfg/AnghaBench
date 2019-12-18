#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_10__ {size_t front_buf; int width; int height; scalar_t__* offsets; scalar_t__* map; TYPE_2__* picture; int /*<<< orphan*/ * fb; int /*<<< orphan*/  plane_id; int /*<<< orphan*/  crtc; int /*<<< orphan*/  drm_fd; } ;
typedef  TYPE_4__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_8__ {TYPE_1__* p; } ;
struct TYPE_7__ {scalar_t__ p_pixels; } ;

/* Variables and functions */
 size_t MAXHWBUF ; 
 int PICTURE_PLANE_MAX ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ drmModeSetPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *picture)
{
    VLC_UNUSED(picture);
    vout_display_sys_t *sys = vd->sys;
    int i;

    if (drmModeSetPlane(sys->drm_fd, sys->plane_id, sys->crtc,
                         sys->fb[sys->front_buf], 0,
                         0, 0, sys->width, sys->height,
                         0, 0, sys->width << 16, sys->height << 16)) {
        msg_Err(vd, "Cannot do set plane for plane id %u, fb %x",
                sys->plane_id,
                sys->fb[sys->front_buf]);
    } else {
        sys->front_buf++;
        sys->front_buf %= MAXHWBUF;

        for (i = 0; i < PICTURE_PLANE_MAX; i++)
            sys->picture->p[i].p_pixels =
                    sys->map[sys->front_buf]+sys->offsets[i];
    }
}