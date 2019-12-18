#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_picture; int /*<<< orphan*/  p_text; int /*<<< orphan*/  i_alpha; int /*<<< orphan*/  i_align; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_3__ subpicture_region_t ;
struct TYPE_8__ {int i_planes; TYPE_1__* p; } ;
struct TYPE_7__ {int i_lines; int i_pitch; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* subpicture_region_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_segment_Copy (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

subpicture_region_t* subpicture_region_Copy( subpicture_region_t *p_region_src )
{
    if (!p_region_src)
        return NULL;
    subpicture_region_t *p_region_dst = subpicture_region_New(&p_region_src->fmt);
    if (unlikely(!p_region_dst))
        return NULL;

    p_region_dst->i_x      = p_region_src->i_x;
    p_region_dst->i_y      = p_region_src->i_y;
    p_region_dst->i_align  = p_region_src->i_align;
    p_region_dst->i_alpha  = p_region_src->i_alpha;

    p_region_dst->p_text = text_segment_Copy( p_region_src->p_text );

    //Palette is already copied by subpicture_region_New, we just have to duplicate p_pixels
    for (int i = 0; i < p_region_src->p_picture->i_planes; i++)
        memcpy(p_region_dst->p_picture->p[i].p_pixels,
               p_region_src->p_picture->p[i].p_pixels,
               p_region_src->p_picture->p[i].i_lines * p_region_src->p_picture->p[i].i_pitch);
    return p_region_dst;
}