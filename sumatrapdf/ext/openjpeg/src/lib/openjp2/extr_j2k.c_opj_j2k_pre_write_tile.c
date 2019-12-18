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
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_10__ {scalar_t__ m_current_poc_tile_part_number; scalar_t__ m_current_tile_part_number; } ;
struct TYPE_11__ {TYPE_3__ m_encoder; } ;
struct TYPE_9__ {int tw; int th; TYPE_1__* tcps; } ;
struct TYPE_12__ {size_t m_current_tile_number; TYPE_6__* m_tcd; TYPE_4__ m_specific_param; TYPE_2__ m_cp; } ;
typedef  TYPE_5__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_13__ {int /*<<< orphan*/  cur_totnum_tp; } ;
struct TYPE_8__ {int /*<<< orphan*/  m_nb_tile_parts; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opj_tcd_init_encode_tile (TYPE_6__*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_pre_write_tile(opj_j2k_t * p_j2k,
                                       OPJ_UINT32 p_tile_index,
                                       opj_stream_private_t *p_stream,
                                       opj_event_mgr_t * p_manager)
{
    (void)p_stream;
    if (p_tile_index != p_j2k->m_current_tile_number) {
        opj_event_msg(p_manager, EVT_ERROR, "The given tile index does not match.");
        return OPJ_FALSE;
    }

    opj_event_msg(p_manager, EVT_INFO, "tile number %d / %d\n",
                  p_j2k->m_current_tile_number + 1, p_j2k->m_cp.tw * p_j2k->m_cp.th);

    p_j2k->m_specific_param.m_encoder.m_current_tile_part_number = 0;
    p_j2k->m_tcd->cur_totnum_tp = p_j2k->m_cp.tcps[p_tile_index].m_nb_tile_parts;
    p_j2k->m_specific_param.m_encoder.m_current_poc_tile_part_number = 0;

    /* initialisation before tile encoding  */
    if (! opj_tcd_init_encode_tile(p_j2k->m_tcd, p_j2k->m_current_tile_number,
                                   p_manager)) {
        return OPJ_FALSE;
    }

    return OPJ_TRUE;
}