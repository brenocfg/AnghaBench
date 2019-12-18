#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_3__ {int /*<<< orphan*/  j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_read_tile_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_jp2_read_tile_header(opj_jp2_t * p_jp2,
                                  OPJ_UINT32 * p_tile_index,
                                  OPJ_UINT32 * p_data_size,
                                  OPJ_INT32 * p_tile_x0,
                                  OPJ_INT32 * p_tile_y0,
                                  OPJ_INT32 * p_tile_x1,
                                  OPJ_INT32 * p_tile_y1,
                                  OPJ_UINT32 * p_nb_comps,
                                  OPJ_BOOL * p_go_on,
                                  opj_stream_private_t *p_stream,
                                  opj_event_mgr_t * p_manager
                                 )
{
    return opj_j2k_read_tile_header(p_jp2->j2k,
                                    p_tile_index,
                                    p_data_size,
                                    p_tile_x0, p_tile_y0,
                                    p_tile_x1, p_tile_y1,
                                    p_nb_comps,
                                    p_go_on,
                                    p_stream,
                                    p_manager);
}