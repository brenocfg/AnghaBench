#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_20__ {int i_sar_num; int i_sar_den; scalar_t__ i_y_offset; scalar_t__ i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_2__ video_format_t ;
struct TYPE_21__ {int b_absolute; int b_ephemer; scalar_t__ i_alpha; TYPE_4__* p_region; scalar_t__ i_stop; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_3__ subpicture_t ;
struct TYPE_22__ {int i_align; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  p_picture; } ;
typedef  TYPE_4__ subpicture_region_t ;
struct TYPE_23__ {TYPE_1__* p; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_24__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ filter_t ;
struct TYPE_26__ {scalar_t__ i_alpha; TYPE_5__* p_pic; } ;
struct TYPE_25__ {int b_absolute; int i_pos; int /*<<< orphan*/  lock; int /*<<< orphan*/  i_pos_y; int /*<<< orphan*/  i_pos_x; int /*<<< orphan*/  b_spu_update; TYPE_8__ p_BarGraph; } ;
typedef  TYPE_7__ filter_sys_t ;
struct TYPE_19__ {int /*<<< orphan*/  i_visible_lines; int /*<<< orphan*/  i_visible_pitch; } ;
typedef  TYPE_8__ BarGraph_t ;

/* Variables and functions */
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 size_t Y_PLANE ; 
 TYPE_3__* filter_NewSubpicture (TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  subpicture_Delete (TYPE_3__*) ; 
 TYPE_4__* subpicture_region_New (TYPE_2__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *FilterSub(filter_t *p_filter, vlc_tick_t date)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    BarGraph_t *p_BarGraph = &(p_sys->p_BarGraph);

    subpicture_t *p_spu;
    subpicture_region_t *p_region;
    video_format_t fmt;
    picture_t *p_pic;

    vlc_mutex_lock(&p_sys->lock);
    /* Basic test:  b_spu_update occurs on a dynamic change */
    if (!p_sys->b_spu_update) {
        vlc_mutex_unlock(&p_sys->lock);
        return NULL;
    }

    p_pic = p_BarGraph->p_pic;

    /* Allocate the subpicture internal data. */
    p_spu = filter_NewSubpicture(p_filter);
    if (!p_spu)
        goto exit;

    p_spu->b_absolute = p_sys->b_absolute;
    p_spu->i_start = date;
    p_spu->i_stop = 0;
    p_spu->b_ephemer = true;

    /* Send an empty subpicture to clear the display when needed */
    if (!p_pic || !p_BarGraph->i_alpha)
        goto exit;

    /* Create new SPU region */
    video_format_Init(&fmt, VLC_CODEC_YUVA);
    fmt.i_sar_num = fmt.i_sar_den = 1;
    fmt.i_width = fmt.i_visible_width = p_pic->p[Y_PLANE].i_visible_pitch;
    fmt.i_height = fmt.i_visible_height = p_pic->p[Y_PLANE].i_visible_lines;
    fmt.i_x_offset = fmt.i_y_offset = 0;
    p_region = subpicture_region_New(&fmt);
    if (!p_region) {
        msg_Err(p_filter, "cannot allocate SPU region");
        subpicture_Delete(p_spu);
        p_spu = NULL;
        goto exit;
    }

    /* */
    picture_Copy(p_region->p_picture, p_pic);

    /*  where to locate the bar graph: */
    if (p_sys->i_pos < 0) {   /*  set to an absolute xy */
        p_region->i_align = SUBPICTURE_ALIGN_RIGHT | SUBPICTURE_ALIGN_TOP;
        p_spu->b_absolute = true;
    } else {   /* set to one of the 9 relative locations */
        p_region->i_align = p_sys->i_pos;
        p_spu->b_absolute = false;
    }

    p_region->i_x = p_sys->i_pos_x;
    p_region->i_y = p_sys->i_pos_y;

    p_spu->p_region = p_region;

    p_spu->i_alpha = p_BarGraph->i_alpha ;

exit:
    vlc_mutex_unlock(&p_sys->lock);

    return p_spu;
}