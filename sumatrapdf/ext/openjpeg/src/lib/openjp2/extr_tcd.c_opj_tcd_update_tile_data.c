#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_13__ {int minimum_num_resolutions; int /*<<< orphan*/  const* data_win; int /*<<< orphan*/  const* data; TYPE_6__* resolutions; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_14__ {scalar_t__ whole_tile_decoding; TYPE_3__* image; TYPE_2__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_15__ {scalar_t__ win_x1; scalar_t__ win_x0; scalar_t__ win_y1; scalar_t__ win_y0; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_16__ {int prec; int resno_decoded; int /*<<< orphan*/  sgnd; } ;
typedef  TYPE_7__ opj_image_comp_t ;
struct TYPE_12__ {scalar_t__ numcomps; TYPE_7__* comps; } ;
struct TYPE_11__ {TYPE_1__* tiles; } ;
struct TYPE_10__ {TYPE_4__* comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int /*<<< orphan*/  const OPJ_INT32 ;
typedef  int /*<<< orphan*/  const OPJ_INT16 ;
typedef  void* OPJ_CHAR ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ opj_tcd_get_decoded_tile_size (TYPE_5__*,int /*<<< orphan*/ ) ; 

OPJ_BOOL opj_tcd_update_tile_data(opj_tcd_t *p_tcd,
                                  OPJ_BYTE * p_dest,
                                  OPJ_UINT32 p_dest_length
                                 )
{
    OPJ_UINT32 i, j, k, l_data_size = 0;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_tilecomp_t * l_tilec = 00;
    opj_tcd_resolution_t * l_res;
    OPJ_UINT32 l_size_comp, l_remaining;
    OPJ_UINT32 l_stride, l_width, l_height;

    l_data_size = opj_tcd_get_decoded_tile_size(p_tcd, OPJ_TRUE);
    if (l_data_size == UINT_MAX || l_data_size > p_dest_length) {
        return OPJ_FALSE;
    }

    l_tilec = p_tcd->tcd_image->tiles->comps;
    l_img_comp = p_tcd->image->comps;

    for (i = 0; i < p_tcd->image->numcomps; ++i) {
        const OPJ_INT32* l_src_data;
        l_size_comp = l_img_comp->prec >> 3; /*(/ 8)*/
        l_remaining = l_img_comp->prec & 7;  /* (%8) */
        l_res = l_tilec->resolutions + l_img_comp->resno_decoded;
        if (p_tcd->whole_tile_decoding) {
            l_width = (OPJ_UINT32)(l_res->x1 - l_res->x0);
            l_height = (OPJ_UINT32)(l_res->y1 - l_res->y0);
            l_stride = (OPJ_UINT32)(l_tilec->resolutions[l_tilec->minimum_num_resolutions -
                                                                     1].x1 -
                                    l_tilec->resolutions[l_tilec->minimum_num_resolutions - 1].x0) - l_width;
            l_src_data = l_tilec->data;
        } else {
            l_width = l_res->win_x1 - l_res->win_x0;
            l_height = l_res->win_y1 - l_res->win_y0;
            l_stride = 0;
            l_src_data = l_tilec->data_win;
        }

        if (l_remaining) {
            ++l_size_comp;
        }

        if (l_size_comp == 3) {
            l_size_comp = 4;
        }

        switch (l_size_comp) {
        case 1: {
            OPJ_CHAR * l_dest_ptr = (OPJ_CHAR *) p_dest;
            const OPJ_INT32 * l_src_ptr = l_src_data;

            if (l_img_comp->sgnd) {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr++) = (OPJ_CHAR)(*(l_src_ptr++));
                    }
                    l_src_ptr += l_stride;
                }
            } else {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr++) = (OPJ_CHAR)((*(l_src_ptr++)) & 0xff);
                    }
                    l_src_ptr += l_stride;
                }
            }

            p_dest = (OPJ_BYTE *)l_dest_ptr;
        }
        break;
        case 2: {
            const OPJ_INT32 * l_src_ptr = l_src_data;
            OPJ_INT16 * l_dest_ptr = (OPJ_INT16 *) p_dest;

            if (l_img_comp->sgnd) {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        OPJ_INT16 val = (OPJ_INT16)(*(l_src_ptr++));
                        memcpy(l_dest_ptr, &val, sizeof(val));
                        l_dest_ptr ++;
                    }
                    l_src_ptr += l_stride;
                }
            } else {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        OPJ_INT16 val = (OPJ_INT16)((*(l_src_ptr++)) & 0xffff);
                        memcpy(l_dest_ptr, &val, sizeof(val));
                        l_dest_ptr ++;
                    }
                    l_src_ptr += l_stride;
                }
            }

            p_dest = (OPJ_BYTE*) l_dest_ptr;
        }
        break;
        case 4: {
            OPJ_INT32 * l_dest_ptr = (OPJ_INT32 *) p_dest;
            const OPJ_INT32 * l_src_ptr = l_src_data;

            for (j = 0; j < l_height; ++j) {
                memcpy(l_dest_ptr, l_src_ptr, l_width * sizeof(OPJ_INT32));
                l_dest_ptr += l_width;
                l_src_ptr += l_width + l_stride;
            }

            p_dest = (OPJ_BYTE*) l_dest_ptr;
        }
        break;
        }

        ++l_img_comp;
        ++l_tilec;
    }

    return OPJ_TRUE;
}