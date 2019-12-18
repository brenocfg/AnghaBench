#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int num_pics; struct deint_data* const pp_pics; } ;
struct TYPE_8__ {struct deint_data* const surfaces; } ;
struct deint_data {TYPE_1__ history; TYPE_2__ forward_refs; } ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_10__ {struct deint_data* p_data; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (TYPE_3__* const,TYPE_4__* const) ; 
 int /*<<< orphan*/  free (struct deint_data* const) ; 
 int /*<<< orphan*/  picture_Release (struct deint_data) ; 

__attribute__((used)) static void
CloseDeinterlace(vlc_object_t * obj)
{
    filter_t *const             filter = (filter_t *)obj;
    filter_sys_t *const         filter_sys = filter->p_sys;
    struct deint_data *const    p_data = filter_sys->p_data;

    if (p_data->forward_refs.surfaces)
        free(p_data->forward_refs.surfaces);
    if (p_data->history.pp_pics)
    {
        while (p_data->history.num_pics)
            picture_Release(p_data->history.pp_pics[--p_data->history.num_pics]);
        free(p_data->history.pp_pics);
    }
    free(p_data);
    Close(filter, filter_sys);
}