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
struct TYPE_4__ {TYPE_2__** pp_cur_pic; } ;
struct deint_data {int cur_frame; TYPE_1__ history; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ VAProcFilterParameterBufferDeinterlacing ;
struct TYPE_5__ {scalar_t__ b_top_field_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  VA_DEINTERLACING_BOTTOM_FIELD ; 
 int /*<<< orphan*/  VA_DEINTERLACING_BOTTOM_FIELD_FIRST ; 

__attribute__((used)) static void
Deinterlace_UpdateFilterParams(void * p_data, void * va_params)
{
    struct deint_data *const    p_deint_data = p_data;
    VAProcFilterParameterBufferDeinterlacing *const      p_va_params = va_params;

    p_va_params->flags =
        p_deint_data->history.pp_cur_pic[0]->b_top_field_first ?
        0 : VA_DEINTERLACING_BOTTOM_FIELD_FIRST;
    if (p_deint_data->cur_frame ==
        (p_deint_data->history.pp_cur_pic[0]->b_top_field_first ? 1 : 0))
        p_va_params->flags |= VA_DEINTERLACING_BOTTOM_FIELD;
}