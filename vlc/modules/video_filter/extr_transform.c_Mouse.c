#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; } ;
typedef  TYPE_2__ vlc_mouse_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_11__ {TYPE_3__ video; } ;
struct TYPE_14__ {TYPE_5__* p_sys; TYPE_1__ fmt_out; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* convert ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_2__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Mouse(filter_t *filter, vlc_mouse_t *mouse,
                 const vlc_mouse_t *mold, const vlc_mouse_t *mnew)
{
    VLC_UNUSED( mold );

    const video_format_t *fmt = &filter->fmt_out.video;
    const filter_sys_t   *sys = filter->p_sys;

    *mouse = *mnew;
    sys->convert(&mouse->i_x, &mouse->i_y,
                 fmt->i_visible_width, fmt->i_visible_height,
                 mouse->i_x, mouse->i_y);
    return VLC_SUCCESS;
}