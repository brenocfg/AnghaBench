#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* p_window; } ;
typedef  TYPE_4__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_14__ {TYPE_4__* p_vd_sys; } ;
struct TYPE_13__ {int b_vd_ref; int i_index; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_jsurface; int /*<<< orphan*/  p_surface; } ;
struct TYPE_16__ {TYPE_3__ sw; TYPE_2__ hw; } ;
typedef  TYPE_5__ picture_sys_t ;
struct TYPE_17__ {int /*<<< orphan*/  pf_destroy; TYPE_5__* p_sys; } ;
typedef  TYPE_6__ picture_resource_t ;
struct TYPE_12__ {int /*<<< orphan*/  p_jsurface; int /*<<< orphan*/  p_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  AndroidOpaquePicture_DetachVout ; 
 int /*<<< orphan*/  AndroidPicture_Destroy ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * picture_NewFromResource (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *PictureAlloc(vout_display_sys_t *sys, video_format_t *fmt,
                               bool b_opaque)
{
    picture_t *p_pic;
    picture_resource_t rsc;
    picture_sys_t *p_picsys = calloc(1, sizeof(*p_picsys));

    if (unlikely(p_picsys == NULL))
        return NULL;


    memset(&rsc, 0, sizeof(picture_resource_t));
    rsc.p_sys = p_picsys;

    if (b_opaque)
    {
        p_picsys->hw.b_vd_ref = true;
        p_picsys->hw.p_surface = sys->p_window->p_surface;
        p_picsys->hw.p_jsurface =  sys->p_window->p_jsurface;
        p_picsys->hw.i_index = -1;
        vlc_mutex_init(&p_picsys->hw.lock);
        rsc.pf_destroy = AndroidOpaquePicture_DetachVout;
    }
    else
    {
        p_picsys->sw.p_vd_sys = sys;
        rsc.pf_destroy = AndroidPicture_Destroy;
    }

    p_pic = picture_NewFromResource(fmt, &rsc);
    if (!p_pic)
    {
        free(p_picsys);
        return NULL;
    }
    return p_pic;
}