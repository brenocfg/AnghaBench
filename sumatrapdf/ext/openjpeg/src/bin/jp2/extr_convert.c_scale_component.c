#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prec; int* data; scalar_t__ bpp; scalar_t__ sgnd; scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ opj_image_comp_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  scale_component_up (TYPE_1__*,scalar_t__) ; 

void scale_component(opj_image_comp_t* component, OPJ_UINT32 precision)
{
    int shift;
    OPJ_SIZE_T i, len;

    if (component->prec == precision) {
        return;
    }
    if (component->prec < precision) {
        scale_component_up(component, precision);
        return;
    }
    shift = (int)(component->prec - precision);
    len = (OPJ_SIZE_T)component->w * (OPJ_SIZE_T)component->h;
    if (component->sgnd) {
        OPJ_INT32* l_data = component->data;
        for (i = 0; i < len; ++i) {
            l_data[i] >>= shift;
        }
    } else {
        OPJ_UINT32* l_data = (OPJ_UINT32*)component->data;
        for (i = 0; i < len; ++i) {
            l_data[i] >>= shift;
        }
    }
    component->bpp = precision;
    component->prec = precision;
}