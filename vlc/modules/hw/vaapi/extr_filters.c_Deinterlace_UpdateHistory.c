#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_pics; int sz; int /*<<< orphan*/ ** pp_cur_pic; int /*<<< orphan*/ ** pp_pics; } ;
struct deint_data {TYPE_1__ history; } ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *
Deinterlace_UpdateHistory(struct deint_data * p_deint_data, picture_t * src)
{
    if (p_deint_data->history.num_pics == p_deint_data->history.sz)
    {
        picture_Release(*p_deint_data->history.pp_pics);
        memmove(p_deint_data->history.pp_pics, p_deint_data->history.pp_pics + 1,
                --p_deint_data->history.num_pics * sizeof(picture_t *));
    }
    p_deint_data->history.pp_pics[p_deint_data->history.num_pics++] = src;

    return *p_deint_data->history.pp_cur_pic;
}