#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcd_t ;
typedef  int /*<<< orphan*/  opj_tcd_cblk_dec_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  opj_tcd_init_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_tcd_init_decode_tile(opj_tcd_t *p_tcd, OPJ_UINT32 p_tile_no,
                                  opj_event_mgr_t* p_manager)
{
    return opj_tcd_init_tile(p_tcd, p_tile_no, OPJ_FALSE, 0.5F,
                             sizeof(opj_tcd_cblk_dec_t), p_manager);
}