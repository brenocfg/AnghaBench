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
struct TYPE_7__ {int num_pics; int /*<<< orphan*/ ** pp_pics; } ;
struct deint_data {TYPE_1__* meta; TYPE_2__ history; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_9__ {struct deint_data* p_data; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_6__ {int i_nb_fields; int /*<<< orphan*/  date; } ;

/* Variables and functions */
 unsigned int METADATA_SIZE ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Deinterlace_Flush(filter_t *filter)
{
    filter_sys_t *p_sys = filter->p_sys;
    struct deint_data *const p_deint_data = p_sys->p_data;

    while (p_deint_data->history.num_pics)
    {
        picture_t *     pic =
            p_deint_data->history.pp_pics[--p_deint_data->history.num_pics];
        picture_Release(pic);
    }

    for (unsigned int i = 0; i < METADATA_SIZE; ++i)
    {
        p_deint_data->meta[i].date = VLC_TICK_INVALID;
        p_deint_data->meta[i].i_nb_fields = 2;
    }
}