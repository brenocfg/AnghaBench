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
struct TYPE_12__ {int* data; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_13__ {scalar_t__ numcomps; TYPE_4__* comps; } ;
typedef  TYPE_5__ opj_tcd_tile_t ;
struct TYPE_14__ {TYPE_3__* image; TYPE_2__* tcp; TYPE_1__* tcd_image; } ;
typedef  TYPE_6__ opj_tcd_t ;
struct TYPE_15__ {int qmfbid; int m_dc_level_shift; } ;
typedef  TYPE_7__ opj_tccp_t ;
typedef  int /*<<< orphan*/  opj_image_comp_t ;
struct TYPE_11__ {int /*<<< orphan*/ * comps; } ;
struct TYPE_10__ {TYPE_7__* tccps; } ;
struct TYPE_9__ {TYPE_5__* tiles; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_dc_level_shift_encode(opj_tcd_t *p_tcd)
{
    OPJ_UINT32 compno;
    opj_tcd_tilecomp_t * l_tile_comp = 00;
    opj_tccp_t * l_tccp = 00;
    opj_image_comp_t * l_img_comp = 00;
    opj_tcd_tile_t * l_tile;
    OPJ_SIZE_T l_nb_elem, i;
    OPJ_INT32 * l_current_ptr;

    l_tile = p_tcd->tcd_image->tiles;
    l_tile_comp = l_tile->comps;
    l_tccp = p_tcd->tcp->tccps;
    l_img_comp = p_tcd->image->comps;

    for (compno = 0; compno < l_tile->numcomps; compno++) {
        l_current_ptr = l_tile_comp->data;
        l_nb_elem = (OPJ_SIZE_T)(l_tile_comp->x1 - l_tile_comp->x0) *
                    (OPJ_SIZE_T)(l_tile_comp->y1 - l_tile_comp->y0);

        if (l_tccp->qmfbid == 1) {
            for (i = 0; i < l_nb_elem; ++i) {
                *l_current_ptr -= l_tccp->m_dc_level_shift ;
                ++l_current_ptr;
            }
        } else {
            for (i = 0; i < l_nb_elem; ++i) {
                *l_current_ptr = (*l_current_ptr - l_tccp->m_dc_level_shift) * (1 << 11);
                ++l_current_ptr;
            }
        }

        ++l_img_comp;
        ++l_tccp;
        ++l_tile_comp;
    }

    return OPJ_TRUE;
}