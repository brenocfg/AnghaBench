#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int minimum_num_resolutions; TYPE_6__* resolutions; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_13__ {int /*<<< orphan*/  whole_tile_decoding; TYPE_3__* image; TYPE_2__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_14__ {scalar_t__ win_x1; scalar_t__ win_x0; scalar_t__ win_y1; scalar_t__ win_y0; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_15__ {int prec; } ;
typedef  TYPE_7__ opj_image_comp_t ;
struct TYPE_11__ {scalar_t__ numcomps; TYPE_7__* comps; } ;
struct TYPE_10__ {TYPE_1__* tiles; } ;
struct TYPE_9__ {TYPE_4__* comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 

OPJ_UINT32 opj_tcd_get_decoded_tile_size(opj_tcd_t *p_tcd,
        OPJ_BOOL take_into_account_partial_decoding)
{
    OPJ_UINT32 i;
    OPJ_UINT32 l_data_size = 0;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_tilecomp_t * l_tile_comp = 00;
    opj_tcd_resolution_t * l_res = 00;
    OPJ_UINT32 l_size_comp, l_remaining;
    OPJ_UINT32 l_temp;

    l_tile_comp = p_tcd->tcd_image->tiles->comps;
    l_img_comp = p_tcd->image->comps;

    for (i = 0; i < p_tcd->image->numcomps; ++i) {
        OPJ_UINT32 w, h;
        l_size_comp = l_img_comp->prec >> 3; /*(/ 8)*/
        l_remaining = l_img_comp->prec & 7;  /* (%8) */

        if (l_remaining) {
            ++l_size_comp;
        }

        if (l_size_comp == 3) {
            l_size_comp = 4;
        }

        l_res = l_tile_comp->resolutions + l_tile_comp->minimum_num_resolutions - 1;
        if (take_into_account_partial_decoding && !p_tcd->whole_tile_decoding) {
            w = l_res->win_x1 - l_res->win_x0;
            h = l_res->win_y1 - l_res->win_y0;
        } else {
            w = (OPJ_UINT32)(l_res->x1 - l_res->x0);
            h = (OPJ_UINT32)(l_res->y1 - l_res->y0);
        }
        if (h > 0 && UINT_MAX / w < h) {
            return UINT_MAX;
        }
        l_temp = w * h;
        if (l_size_comp && UINT_MAX / l_size_comp < l_temp) {
            return UINT_MAX;
        }
        l_temp *= l_size_comp;

        if (l_temp > UINT_MAX - l_data_size) {
            return UINT_MAX;
        }
        l_data_size += l_temp;
        ++l_img_comp;
        ++l_tile_comp;
    }

    return l_data_size;
}