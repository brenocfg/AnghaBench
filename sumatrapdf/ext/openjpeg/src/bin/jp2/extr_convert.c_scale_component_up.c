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
struct TYPE_3__ {int prec; int bpp; scalar_t__* data; scalar_t__ sgnd; scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ opj_image_comp_t ;
typedef  int OPJ_UINT64 ;
typedef  int OPJ_UINT32 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int OPJ_INT64 ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void scale_component_up(opj_image_comp_t* component,
                               OPJ_UINT32 precision)
{
    OPJ_SIZE_T i, len;

    len = (OPJ_SIZE_T)component->w * (OPJ_SIZE_T)component->h;
    if (component->sgnd) {
        OPJ_INT64  newMax = (OPJ_INT64)(1U << (precision - 1));
        OPJ_INT64  oldMax = (OPJ_INT64)(1U << (component->prec - 1));
        OPJ_INT32* l_data = component->data;
        for (i = 0; i < len; ++i) {
            l_data[i] = (OPJ_INT32)(((OPJ_INT64)l_data[i] * newMax) / oldMax);
        }
    } else {
        OPJ_UINT64  newMax = (OPJ_UINT64)((1U << precision) - 1U);
        OPJ_UINT64  oldMax = (OPJ_UINT64)((1U << component->prec) - 1U);
        OPJ_UINT32* l_data = (OPJ_UINT32*)component->data;
        for (i = 0; i < len; ++i) {
            l_data[i] = (OPJ_UINT32)(((OPJ_UINT64)l_data[i] * newMax) / oldMax);
        }
    }
    component->prec = precision;
    component->bpp = precision;
}