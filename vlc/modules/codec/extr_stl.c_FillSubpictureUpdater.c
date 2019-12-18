#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  inner_align; int /*<<< orphan*/  align; int /*<<< orphan*/ * p_segments; } ;
struct TYPE_7__ {TYPE_1__ region; } ;
typedef  TYPE_2__ subtext_updater_sys_t ;
struct TYPE_8__ {int i_justify; int /*<<< orphan*/ * p_segment; int /*<<< orphan*/ ** pp_segment_last; scalar_t__ i_accumulating; } ;
typedef  TYPE_3__ stl_sg_t ;

/* Variables and functions */
 int /*<<< orphan*/  SUBPICTURE_ALIGN_BOTTOM ; 
 int /*<<< orphan*/  SUBPICTURE_ALIGN_LEFT ; 
 int /*<<< orphan*/  SUBPICTURE_ALIGN_RIGHT ; 
 int /*<<< orphan*/ * text_segment_Copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FillSubpictureUpdater(stl_sg_t *p_group, subtext_updater_sys_t *p_spu_sys)
{
    if(p_group->i_accumulating)
    {
        p_spu_sys->region.p_segments = text_segment_Copy(p_group->p_segment);
    }
    else
    {
        p_spu_sys->region.p_segments = p_group->p_segment;
        p_group->p_segment = NULL;
        p_group->pp_segment_last = &p_group->p_segment;
    }

    p_spu_sys->region.align = SUBPICTURE_ALIGN_BOTTOM;
    if(p_group->i_justify == 0x01)
        p_spu_sys->region.inner_align = SUBPICTURE_ALIGN_LEFT;
    else if(p_group->i_justify == 0x03)
        p_spu_sys->region.inner_align = SUBPICTURE_ALIGN_RIGHT;
}