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
struct TYPE_3__ {int /*<<< orphan*/  drv_value; } ;
struct basic_filter_data {TYPE_1__ sigma; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ VAProcFilterParameterBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_load_float (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
BasicFilter_UpdateVAFilterParams(void * p_data, void * va_params)
{
    struct basic_filter_data *const     p_basic_filter_data = p_data;
    VAProcFilterParameterBuffer *const  p_va_param = va_params;

    p_va_param->value =
        vlc_atomic_load_float(&p_basic_filter_data->sigma.drv_value);
}