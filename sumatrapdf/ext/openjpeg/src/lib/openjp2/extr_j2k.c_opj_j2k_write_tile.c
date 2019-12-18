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
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_12__ {TYPE_5__* m_tcd; } ;
typedef  TYPE_4__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_13__ {TYPE_3__* tcd_image; TYPE_1__* image; } ;
struct TYPE_11__ {TYPE_2__* tiles; } ;
struct TYPE_10__ {int /*<<< orphan*/ * comps; } ;
struct TYPE_9__ {scalar_t__ numcomps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_alloc_tile_component_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opj_j2k_post_write_tile (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_pre_write_tile (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_tcd_copy_tile_data (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__) ; 

OPJ_BOOL opj_j2k_write_tile(opj_j2k_t * p_j2k,
                            OPJ_UINT32 p_tile_index,
                            OPJ_BYTE * p_data,
                            OPJ_UINT32 p_data_size,
                            opj_stream_private_t *p_stream,
                            opj_event_mgr_t * p_manager)
{
    if (! opj_j2k_pre_write_tile(p_j2k, p_tile_index, p_stream, p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Error while opj_j2k_pre_write_tile with tile index = %d\n", p_tile_index);
        return OPJ_FALSE;
    } else {
        OPJ_UINT32 j;
        /* Allocate data */
        for (j = 0; j < p_j2k->m_tcd->image->numcomps; ++j) {
            opj_tcd_tilecomp_t* l_tilec = p_j2k->m_tcd->tcd_image->tiles->comps + j;

            if (! opj_alloc_tile_component_data(l_tilec)) {
                opj_event_msg(p_manager, EVT_ERROR, "Error allocating tile component data.");
                return OPJ_FALSE;
            }
        }

        /* now copy data into the tile component */
        if (! opj_tcd_copy_tile_data(p_j2k->m_tcd, p_data, p_data_size)) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Size mismatch between tile data and sent data.");
            return OPJ_FALSE;
        }
        if (! opj_j2k_post_write_tile(p_j2k, p_stream, p_manager)) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Error while opj_j2k_post_write_tile with tile index = %d\n", p_tile_index);
            return OPJ_FALSE;
        }
    }

    return OPJ_TRUE;
}