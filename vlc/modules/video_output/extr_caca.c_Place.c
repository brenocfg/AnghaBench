#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  source; TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {int x; int y; int width; int height; } ;
struct TYPE_6__ {TYPE_3__ place; int /*<<< orphan*/  dp; int /*<<< orphan*/  cv; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;

/* Variables and functions */
 int caca_get_display_height (int /*<<< orphan*/ ) ; 
 int caca_get_display_width (int /*<<< orphan*/ ) ; 
 int cucul_get_canvas_height (int /*<<< orphan*/ ) ; 
 int cucul_get_canvas_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_display_PlacePicture (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void Place(vout_display_t *vd, const vout_display_cfg_t *cfg)
{
    vout_display_sys_t *sys = vd->sys;

    vout_display_PlacePicture(&sys->place, &vd->source, cfg);

    const int canvas_width   = cucul_get_canvas_width(sys->cv);
    const int canvas_height  = cucul_get_canvas_height(sys->cv);
    const int display_width  = caca_get_display_width(sys->dp);
    const int display_height = caca_get_display_height(sys->dp);

    if (display_width > 0 && display_height > 0) {
        sys->place.x      =  sys->place.x      * canvas_width  / display_width;
        sys->place.y      =  sys->place.y      * canvas_height / display_height;
        sys->place.width  = (sys->place.width  * canvas_width  + display_width/2)  / display_width;
        sys->place.height = (sys->place.height * canvas_height + display_height/2) / display_height;
    } else {
        sys->place.x = 0;
        sys->place.y = 0;
        sys->place.width  = canvas_width;
        sys->place.height = display_height;
    }
}