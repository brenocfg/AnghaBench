#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  min_luminance; int /*<<< orphan*/  max_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ * primaries; } ;
struct TYPE_5__ {TYPE_1__ mastering; } ;
typedef  TYPE_2__ video_format_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * box_new (char*) ; 

__attribute__((used)) static bo_t *GetMdcv(const video_format_t *p_vfmt)
{
    if(!p_vfmt->mastering.max_luminance)
        return NULL;
    bo_t *p_box = box_new("mdcv");
    if(p_box)
    {
        for(int i=0; i<6; i++)
            bo_add_16be(p_box, p_vfmt->mastering.primaries[i]);
        bo_add_16be(p_box, p_vfmt->mastering.white_point[0]);
        bo_add_16be(p_box, p_vfmt->mastering.white_point[1]);
        bo_add_32be(p_box, p_vfmt->mastering.max_luminance);
        bo_add_32be(p_box, p_vfmt->mastering.min_luminance);
    }
    return p_box;
}