#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* data; int prec; scalar_t__ sgnd; scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ opj_image_comp_t ;
typedef  int OPJ_UINT32 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;

/* Variables and functions */

void clip_component(opj_image_comp_t* component, OPJ_UINT32 precision)
{
    OPJ_SIZE_T i;
    OPJ_SIZE_T len;
    OPJ_UINT32 umax = (OPJ_UINT32)((OPJ_INT32) - 1);

    len = (OPJ_SIZE_T)component->w * (OPJ_SIZE_T)component->h;
    if (precision < 32) {
        umax = (1U << precision) - 1U;
    }

    if (component->sgnd) {
        OPJ_INT32* l_data = component->data;
        OPJ_INT32 max = (OPJ_INT32)(umax / 2U);
        OPJ_INT32 min = -max - 1;
        for (i = 0; i < len; ++i) {
            if (l_data[i] > max) {
                l_data[i] = max;
            } else if (l_data[i] < min) {
                l_data[i] = min;
            }
        }
    } else {
        OPJ_UINT32* l_data = (OPJ_UINT32*)component->data;
        for (i = 0; i < len; ++i) {
            if (l_data[i] > umax) {
                l_data[i] = umax;
            }
        }
    }
    component->prec = precision;
}