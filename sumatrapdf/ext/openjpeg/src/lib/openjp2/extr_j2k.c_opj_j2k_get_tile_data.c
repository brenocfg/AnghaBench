#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;
struct TYPE_11__ {TYPE_2__* tcd_image; TYPE_4__* image; } ;
typedef  TYPE_3__ opj_tcd_t ;
struct TYPE_12__ {scalar_t__ numcomps; TYPE_5__* comps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_13__ {int* data; int /*<<< orphan*/  sgnd; } ;
typedef  TYPE_5__ opj_image_comp_t ;
struct TYPE_10__ {TYPE_1__* tiles; } ;
struct TYPE_9__ {int /*<<< orphan*/ * comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  void* OPJ_INT16 ;
typedef  int /*<<< orphan*/  OPJ_CHAR ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  opj_get_tile_dimensions (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void opj_j2k_get_tile_data(opj_tcd_t * p_tcd, OPJ_BYTE * p_data)
{
    OPJ_UINT32 i, j, k = 0;

    for (i = 0; i < p_tcd->image->numcomps; ++i) {
        opj_image_t * l_image =  p_tcd->image;
        OPJ_INT32 * l_src_ptr;
        opj_tcd_tilecomp_t * l_tilec = p_tcd->tcd_image->tiles->comps + i;
        opj_image_comp_t * l_img_comp = l_image->comps + i;
        OPJ_UINT32 l_size_comp, l_width, l_height, l_offset_x, l_offset_y,
                   l_image_width, l_stride, l_tile_offset;

        opj_get_tile_dimensions(l_image,
                                l_tilec,
                                l_img_comp,
                                &l_size_comp,
                                &l_width,
                                &l_height,
                                &l_offset_x,
                                &l_offset_y,
                                &l_image_width,
                                &l_stride,
                                &l_tile_offset);

        l_src_ptr = l_img_comp->data + l_tile_offset;

        switch (l_size_comp) {
        case 1: {
            OPJ_CHAR * l_dest_ptr = (OPJ_CHAR*) p_data;
            if (l_img_comp->sgnd) {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr) = (OPJ_CHAR)(*l_src_ptr);
                        ++l_dest_ptr;
                        ++l_src_ptr;
                    }
                    l_src_ptr += l_stride;
                }
            } else {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr) = (OPJ_CHAR)((*l_src_ptr) & 0xff);
                        ++l_dest_ptr;
                        ++l_src_ptr;
                    }
                    l_src_ptr += l_stride;
                }
            }

            p_data = (OPJ_BYTE*) l_dest_ptr;
        }
        break;
        case 2: {
            OPJ_INT16 * l_dest_ptr = (OPJ_INT16 *) p_data;
            if (l_img_comp->sgnd) {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr++) = (OPJ_INT16)(*(l_src_ptr++));
                    }
                    l_src_ptr += l_stride;
                }
            } else {
                for (j = 0; j < l_height; ++j) {
                    for (k = 0; k < l_width; ++k) {
                        *(l_dest_ptr++) = (OPJ_INT16)((*(l_src_ptr++)) & 0xffff);
                    }
                    l_src_ptr += l_stride;
                }
            }

            p_data = (OPJ_BYTE*) l_dest_ptr;
        }
        break;
        case 4: {
            OPJ_INT32 * l_dest_ptr = (OPJ_INT32 *) p_data;
            for (j = 0; j < l_height; ++j) {
                for (k = 0; k < l_width; ++k) {
                    *(l_dest_ptr++) = *(l_src_ptr++);
                }
                l_src_ptr += l_stride;
            }

            p_data = (OPJ_BYTE*) l_dest_ptr;
        }
        break;
        }
    }
}