#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ num_pics; scalar_t__ sz; } ;
struct deint_data {TYPE_1__ history; } ;
struct TYPE_14__ {int b_progressive; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_16__ {struct deint_data* p_data; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Deinterlace_UpdateFilterParams ; 
 TYPE_2__* Deinterlace_UpdateHistory (struct deint_data* const,TYPE_2__*) ; 
 int /*<<< orphan*/  Deinterlace_UpdatePipelineParams ; 
 int /*<<< orphan*/  Deinterlace_UpdateReferenceFrames ; 
 TYPE_2__* Filter (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *
Deinterlace(filter_t * filter, picture_t * src)
{
    filter_sys_t *const         filter_sys = filter->p_sys;
    struct deint_data *const    p_deint_data = filter_sys->p_data;

    src = Deinterlace_UpdateHistory(p_deint_data, src);
    if (p_deint_data->history.num_pics < p_deint_data->history.sz)
        return NULL;

    picture_t *const    dest =
        Filter(filter, src,
               Deinterlace_UpdateFilterParams,
               Deinterlace_UpdateReferenceFrames,
               Deinterlace_UpdatePipelineParams);

    if (dest)
        dest->b_progressive = true;

    return dest;
}