#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pp_pics; } ;
struct TYPE_5__ {int sz; void** surfaces; } ;
struct TYPE_4__ {unsigned int sz; void** surfaces; } ;
struct deint_data {TYPE_3__ history; TYPE_2__ forward_refs; TYPE_1__ backward_refs; } ;

/* Variables and functions */
 void* vlc_vaapi_PicGetSurface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Deinterlace_UpdateReferenceFrames(void * p_data)
{
    struct deint_data *const    p_deint_data = p_data;

    if (p_deint_data->backward_refs.sz)
        for (unsigned int i = 0; i < p_deint_data->backward_refs.sz; ++i)
        {
            unsigned int const  idx = p_deint_data->forward_refs.sz + 1 + i;

            p_deint_data->backward_refs.surfaces[i] =
                vlc_vaapi_PicGetSurface(p_deint_data->history.pp_pics[idx]);
        }

    if (p_deint_data->forward_refs.sz)
        for (unsigned int i = 0; i < p_deint_data->forward_refs.sz; ++i)
        {
            unsigned int const  idx = p_deint_data->forward_refs.sz - 1 - i;

            p_deint_data->forward_refs.surfaces[i] =
                vlc_vaapi_PicGetSurface(p_deint_data->history.pp_pics[idx]);
        }
}