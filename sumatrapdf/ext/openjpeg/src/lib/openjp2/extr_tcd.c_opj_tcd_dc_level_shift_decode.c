#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* data_win; int minimum_num_resolutions; int* data; size_t data_size; TYPE_7__* resolutions; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_15__ {size_t numcomps; TYPE_4__* comps; } ;
typedef  TYPE_5__ opj_tcd_tile_t ;
struct TYPE_16__ {int /*<<< orphan*/  whole_tile_decoding; int /*<<< orphan*/ * used_component; TYPE_3__* image; TYPE_2__* tcp; TYPE_1__* tcd_image; } ;
typedef  TYPE_6__ opj_tcd_t ;
struct TYPE_17__ {size_t win_x1; size_t win_x0; size_t win_y1; size_t win_y0; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_7__ opj_tcd_resolution_t ;
struct TYPE_18__ {int qmfbid; scalar_t__ m_dc_level_shift; } ;
typedef  TYPE_8__ opj_tccp_t ;
struct TYPE_19__ {int resno_decoded; int prec; scalar_t__ sgnd; } ;
typedef  TYPE_9__ opj_image_comp_t ;
struct TYPE_13__ {TYPE_9__* comps; } ;
struct TYPE_12__ {TYPE_8__* tccps; } ;
struct TYPE_11__ {TYPE_5__* tiles; } ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT64 ;
typedef  int OPJ_INT32 ;
typedef  scalar_t__ OPJ_FLOAT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ opj_int64_clamp (scalar_t__,int,int) ; 
 int opj_int_clamp (scalar_t__,int,int) ; 
 int /*<<< orphan*/  opj_lrintf (scalar_t__) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_dc_level_shift_decode(opj_tcd_t *p_tcd)
{
    OPJ_UINT32 compno;
    opj_tcd_tilecomp_t * l_tile_comp = 00;
    opj_tccp_t * l_tccp = 00;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_resolution_t* l_res = 00;
    opj_tcd_tile_t * l_tile;
    OPJ_UINT32 l_width, l_height, i, j;
    OPJ_INT32 * l_current_ptr;
    OPJ_INT32 l_min, l_max;
    OPJ_UINT32 l_stride;

    l_tile = p_tcd->tcd_image->tiles;
    l_tile_comp = l_tile->comps;
    l_tccp = p_tcd->tcp->tccps;
    l_img_comp = p_tcd->image->comps;

    for (compno = 0; compno < l_tile->numcomps;
            compno++, ++l_img_comp, ++l_tccp, ++l_tile_comp) {

        if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
            continue;
        }

        l_res = l_tile_comp->resolutions + l_img_comp->resno_decoded;

        if (!p_tcd->whole_tile_decoding) {
            l_width = l_res->win_x1 - l_res->win_x0;
            l_height = l_res->win_y1 - l_res->win_y0;
            l_stride = 0;
            l_current_ptr = l_tile_comp->data_win;
        } else {
            l_width = (OPJ_UINT32)(l_res->x1 - l_res->x0);
            l_height = (OPJ_UINT32)(l_res->y1 - l_res->y0);
            l_stride = (OPJ_UINT32)(
                           l_tile_comp->resolutions[l_tile_comp->minimum_num_resolutions - 1].x1 -
                           l_tile_comp->resolutions[l_tile_comp->minimum_num_resolutions - 1].x0)
                       - l_width;
            l_current_ptr = l_tile_comp->data;

            assert(l_height == 0 ||
                   l_width + l_stride <= l_tile_comp->data_size / l_height); /*MUPDF*/
        }

        if (l_img_comp->sgnd) {
            l_min = -(1 << (l_img_comp->prec - 1));
            l_max = (1 << (l_img_comp->prec - 1)) - 1;
        } else {
            l_min = 0;
            l_max = (OPJ_INT32)((1U << l_img_comp->prec) - 1);
        }


        if (l_tccp->qmfbid == 1) {
            for (j = 0; j < l_height; ++j) {
                for (i = 0; i < l_width; ++i) {
                    /* TODO: do addition on int64 ? */
                    *l_current_ptr = opj_int_clamp(*l_current_ptr + l_tccp->m_dc_level_shift, l_min,
                                                   l_max);
                    ++l_current_ptr;
                }
                l_current_ptr += l_stride;
            }
        } else {
            for (j = 0; j < l_height; ++j) {
                for (i = 0; i < l_width; ++i) {
                    OPJ_FLOAT32 l_value = *((OPJ_FLOAT32 *) l_current_ptr);
                    if (l_value > INT_MAX) {
                        *l_current_ptr = l_max;
                    } else if (l_value < INT_MIN) {
                        *l_current_ptr = l_min;
                    } else {
                        /* Do addition on int64 to avoid overflows */
                        OPJ_INT64 l_value_int = (OPJ_INT64)opj_lrintf(l_value);
                        *l_current_ptr = (OPJ_INT32)opj_int64_clamp(
                                             l_value_int + l_tccp->m_dc_level_shift, l_min, l_max);
                    }
                    ++l_current_ptr;
                }
                l_current_ptr += l_stride;
            }
        }
    }

    return OPJ_TRUE;
}