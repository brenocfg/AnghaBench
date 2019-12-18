#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  fmt; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pool; scalar_t__ picture; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; scalar_t__* offsets; scalar_t__* map; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  rsc ;
struct TYPE_13__ {TYPE_3__* p_voutsys; } ;
typedef  TYPE_4__ picture_sys_t ;
struct TYPE_14__ {int /*<<< orphan*/  pf_destroy; TYPE_4__* p_sys; TYPE_1__* p; } ;
typedef  TYPE_5__ picture_resource_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; scalar_t__ p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  CustomDestroyPicture ; 
 int PICTURE_PLANE_MAX ; 
 int /*<<< orphan*/  VLC_UNUSED (unsigned int) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ picture_NewFromResource (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 
 int /*<<< orphan*/ * picture_pool_New (int,scalar_t__*) ; 

__attribute__((used)) static picture_pool_t *Pool(vout_display_t *vd, unsigned count)
{
    VLC_UNUSED(count);
    vout_display_sys_t *sys = vd->sys;
    picture_sys_t *psys;
    picture_resource_t rsc;
    int i;

    if (!sys->pool && !sys->picture) {
        memset(&rsc, 0, sizeof(rsc));

        for (i = 0; i < PICTURE_PLANE_MAX; i++) {
            rsc.p[i].p_pixels = sys->map[0]+sys->offsets[i];
            rsc.p[i].i_lines  = sys->height;
            rsc.p[i].i_pitch  = sys->stride;
        }

        psys = calloc(1, sizeof(*psys));
        if (psys == NULL)
            return NULL;

        psys->p_voutsys = sys;
        rsc.p_sys = psys;
        rsc.pf_destroy = CustomDestroyPicture;

        sys->picture = picture_NewFromResource(&vd->fmt, &rsc);

        if (!sys->picture) {
            free((void*)psys);
            return NULL;
        }

        sys->pool = picture_pool_New(1, &sys->picture);
        if (!sys->pool)
            picture_Release(sys->picture);
    }

    return sys->pool;
}