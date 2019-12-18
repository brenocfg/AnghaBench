#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adjust_params {TYPE_1__* sigma; } ;
struct adjust_data {struct adjust_params params; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ VAProcFilterParameterBufferColorBalance ;
struct TYPE_3__ {int /*<<< orphan*/  drv_value; scalar_t__ is_available; } ;

/* Variables and functions */
 unsigned int NUM_ADJUST_MODES ; 
 int /*<<< orphan*/  vlc_atomic_load_float (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Adjust_UpdateVAFilterParams(void * p_data, void * va_params)
{
    struct adjust_data *const   p_adjust_data = p_data;
    struct adjust_params *const p_adjust_params = &p_adjust_data->params;
    VAProcFilterParameterBufferColorBalance *const      p_va_params = va_params;

    unsigned int i = 0;
    for (unsigned int j = 0; j < NUM_ADJUST_MODES; ++j)
        if (p_adjust_params->sigma[j].is_available)
            p_va_params[i++].value =
                vlc_atomic_load_float(&p_adjust_params->sigma[j].drv_value);
}