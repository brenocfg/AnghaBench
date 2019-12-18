#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int sz; scalar_t__ surfaces; } ;
struct TYPE_7__ {unsigned int sz; scalar_t__ surfaces; } ;
struct TYPE_6__ {unsigned int sz; scalar_t__ num_pics; scalar_t__ pp_pics; scalar_t__ pp_cur_pic; } ;
struct deint_data {TYPE_3__ forward_refs; TYPE_2__ backward_refs; TYPE_1__ history; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  VASurfaceID ;
struct TYPE_9__ {unsigned int num_backward_references; unsigned int num_forward_references; } ;
typedef  TYPE_4__ VAProcPipelineCaps ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ calloc (unsigned int const,int) ; 
 scalar_t__ vlc_alloc (unsigned int const,int) ; 

__attribute__((used)) static int
OpenDeinterlace_InitHistory(void * p_data, VAProcPipelineCaps const * pipeline_caps)
{
    struct deint_data *const    p_deint_data = p_data;
    unsigned int const          sz_backward_refs =
        pipeline_caps->num_backward_references;
    unsigned int const          sz_forward_refs =
        pipeline_caps->num_forward_references;
    unsigned int const          history_sz =
        sz_backward_refs + 1 + sz_forward_refs;

    p_deint_data->history.pp_pics = calloc(history_sz, sizeof(picture_t *));
    if (!p_deint_data->history.pp_pics)
        return VLC_ENOMEM;

    p_deint_data->history.pp_cur_pic =
        p_deint_data->history.pp_pics + sz_forward_refs;
    p_deint_data->history.num_pics = 0;
    p_deint_data->history.sz = history_sz;

    if (history_sz - 1)
    {
        p_deint_data->forward_refs.surfaces =
            vlc_alloc(history_sz - 1, sizeof(VASurfaceID));
        if (!p_deint_data->forward_refs.surfaces)
            return VLC_ENOMEM;
    }

    p_deint_data->backward_refs.surfaces =
        p_deint_data->forward_refs.surfaces + sz_forward_refs;

    p_deint_data->backward_refs.sz = sz_backward_refs;
    p_deint_data->forward_refs.sz = sz_forward_refs;

    return VLC_SUCCESS;
}