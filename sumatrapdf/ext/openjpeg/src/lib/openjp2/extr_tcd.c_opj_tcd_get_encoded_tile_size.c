#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_12__ {TYPE_3__* image; TYPE_2__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_13__ {int prec; } ;
typedef  TYPE_6__ opj_image_comp_t ;
struct TYPE_10__ {scalar_t__ numcomps; TYPE_6__* comps; } ;
struct TYPE_9__ {TYPE_1__* tiles; } ;
struct TYPE_8__ {TYPE_4__* comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_SIZE_T ;

/* Variables and functions */

OPJ_SIZE_T opj_tcd_get_encoded_tile_size(opj_tcd_t *p_tcd)
{
    OPJ_UINT32 i;
    OPJ_SIZE_T l_data_size = 0;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_tilecomp_t * l_tilec = 00;
    OPJ_UINT32 l_size_comp, l_remaining;

    l_tilec = p_tcd->tcd_image->tiles->comps;
    l_img_comp = p_tcd->image->comps;
    for (i = 0; i < p_tcd->image->numcomps; ++i) {
        l_size_comp = l_img_comp->prec >> 3; /*(/ 8)*/
        l_remaining = l_img_comp->prec & 7;  /* (%8) */

        if (l_remaining) {
            ++l_size_comp;
        }

        if (l_size_comp == 3) {
            l_size_comp = 4;
        }

        l_data_size += l_size_comp * ((OPJ_SIZE_T)(l_tilec->x1 - l_tilec->x0) *
                                      (OPJ_SIZE_T)(l_tilec->y1 - l_tilec->y0));
        ++l_img_comp;
        ++l_tilec;
    }

    return l_data_size;
}