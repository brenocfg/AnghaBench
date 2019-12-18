#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  pf_update; int /*<<< orphan*/  pf_validate; } ;
typedef  TYPE_1__ subpicture_updater_t ;
struct TYPE_12__ {int b_absolute; int /*<<< orphan*/  i_original_picture_height; int /*<<< orphan*/  i_original_picture_width; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_13__ {int ref_cnt; int /*<<< orphan*/  lock; TYPE_4__* p_overlay; } ;
typedef  TYPE_3__ bluray_spu_updater_sys_t ;
struct TYPE_14__ {TYPE_3__* p_updater; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ bluray_overlay_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  subpictureUpdaterDestroy ; 
 int /*<<< orphan*/  subpictureUpdaterUpdate ; 
 int /*<<< orphan*/  subpictureUpdaterValidate ; 
 TYPE_2__* subpicture_New (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *bluraySubpictureCreate(bluray_overlay_t *p_ov)
{
    bluray_spu_updater_sys_t *p_upd_sys = malloc(sizeof(*p_upd_sys));
    if (unlikely(p_upd_sys == NULL)) {
        return NULL;
    }

    p_upd_sys->p_overlay = p_ov;

    subpicture_updater_t updater = {
        .pf_validate = subpictureUpdaterValidate,
        .pf_update   = subpictureUpdaterUpdate,
        .pf_destroy  = subpictureUpdaterDestroy,
        .p_sys       = p_upd_sys,
    };

    subpicture_t *p_pic = subpicture_New(&updater);
    if (p_pic == NULL) {
        free(p_upd_sys);
        return NULL;
    }

    p_pic->i_original_picture_width = p_ov->width;
    p_pic->i_original_picture_height = p_ov->height;
    p_pic->b_absolute = true;

    vlc_mutex_init(&p_upd_sys->lock);
    p_upd_sys->ref_cnt = 2;

    p_ov->p_updater = p_upd_sys;

    return p_pic;
}