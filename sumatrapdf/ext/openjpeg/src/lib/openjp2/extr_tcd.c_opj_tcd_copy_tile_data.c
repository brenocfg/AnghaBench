#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void** data; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_13__ {TYPE_3__* image; TYPE_2__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_14__ {int prec; int /*<<< orphan*/  sgnd; } ;
typedef  TYPE_6__ opj_image_comp_t ;
struct TYPE_11__ {scalar_t__ numcomps; TYPE_6__* comps; } ;
struct TYPE_10__ {TYPE_1__* tiles; } ;
struct TYPE_9__ {TYPE_4__* comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  void* OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_INT16 ;
typedef  int /*<<< orphan*/  OPJ_CHAR ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ opj_tcd_get_encoded_tile_size (TYPE_5__*) ; 

OPJ_BOOL opj_tcd_copy_tile_data(opj_tcd_t *p_tcd,
                                OPJ_BYTE * p_src,
                                OPJ_SIZE_T p_src_length)
{
    OPJ_UINT32 i;
    OPJ_SIZE_T j;
    OPJ_SIZE_T l_data_size = 0;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_tilecomp_t * l_tilec = 00;
    OPJ_UINT32 l_size_comp, l_remaining;
    OPJ_SIZE_T l_nb_elem;

    l_data_size = opj_tcd_get_encoded_tile_size(p_tcd);
    if (l_data_size != p_src_length) {
        return OPJ_FALSE;
    }

    l_tilec = p_tcd->tcd_image->tiles->comps;
    l_img_comp = p_tcd->image->comps;
    for (i = 0; i < p_tcd->image->numcomps; ++i) {
        l_size_comp = l_img_comp->prec >> 3; /*(/ 8)*/
        l_remaining = l_img_comp->prec & 7;  /* (%8) */
        l_nb_elem = (OPJ_SIZE_T)(l_tilec->x1 - l_tilec->x0) *
                    (OPJ_SIZE_T)(l_tilec->y1 - l_tilec->y0);

        if (l_remaining) {
            ++l_size_comp;
        }

        if (l_size_comp == 3) {
            l_size_comp = 4;
        }

        switch (l_size_comp) {
        case 1: {
            OPJ_CHAR * l_src_ptr = (OPJ_CHAR *) p_src;
            OPJ_INT32 * l_dest_ptr = l_tilec->data;

            if (l_img_comp->sgnd) {
                for (j = 0; j < l_nb_elem; ++j) {
                    *(l_dest_ptr++) = (OPJ_INT32)(*(l_src_ptr++));
                }
            } else {
                for (j = 0; j < l_nb_elem; ++j) {
                    *(l_dest_ptr++) = (*(l_src_ptr++)) & 0xff;
                }
            }

            p_src = (OPJ_BYTE*) l_src_ptr;
        }
        break;
        case 2: {
            OPJ_INT32 * l_dest_ptr = l_tilec->data;
            OPJ_INT16 * l_src_ptr = (OPJ_INT16 *) p_src;

            if (l_img_comp->sgnd) {
                for (j = 0; j < l_nb_elem; ++j) {
                    *(l_dest_ptr++) = (OPJ_INT32)(*(l_src_ptr++));
                }
            } else {
                for (j = 0; j < l_nb_elem; ++j) {
                    *(l_dest_ptr++) = (*(l_src_ptr++)) & 0xffff;
                }
            }

            p_src = (OPJ_BYTE*) l_src_ptr;
        }
        break;
        case 4: {
            OPJ_INT32 * l_src_ptr = (OPJ_INT32 *) p_src;
            OPJ_INT32 * l_dest_ptr = l_tilec->data;

            for (j = 0; j < l_nb_elem; ++j) {
                *(l_dest_ptr++) = (OPJ_INT32)(*(l_src_ptr++));
            }

            p_src = (OPJ_BYTE*) l_src_ptr;
        }
        break;
        }

        ++l_img_comp;
        ++l_tilec;
    }

    return OPJ_TRUE;
}