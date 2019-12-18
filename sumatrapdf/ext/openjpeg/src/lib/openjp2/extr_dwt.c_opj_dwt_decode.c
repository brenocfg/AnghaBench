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
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;
struct TYPE_3__ {int /*<<< orphan*/  thread_pool; scalar_t__ whole_tile_decoding; } ;
typedef  TYPE_1__ opj_tcd_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_dwt_decode_partial_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_dwt_decode_tile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

OPJ_BOOL opj_dwt_decode(opj_tcd_t *p_tcd, opj_tcd_tilecomp_t* tilec,
                        OPJ_UINT32 numres)
{
    if (p_tcd->whole_tile_decoding) {
        return opj_dwt_decode_tile(p_tcd->thread_pool, tilec, numres);
    } else {
        return opj_dwt_decode_partial_tile(tilec, numres);
    }
}