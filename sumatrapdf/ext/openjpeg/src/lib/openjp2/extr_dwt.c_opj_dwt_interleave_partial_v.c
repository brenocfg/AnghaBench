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
typedef  int /*<<< orphan*/  opj_sparse_array_int32_t ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  OPJ_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_sparse_array_int32_read (int /*<<< orphan*/ *,int,int,int,int,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_dwt_interleave_partial_v(OPJ_INT32 *dest,
        OPJ_INT32 cas,
        opj_sparse_array_int32_t* sa,
        OPJ_UINT32 sa_col,
        OPJ_UINT32 nb_cols,
        OPJ_UINT32 sn,
        OPJ_UINT32 win_l_y0,
        OPJ_UINT32 win_l_y1,
        OPJ_UINT32 win_h_y0,
        OPJ_UINT32 win_h_y1)
{
    OPJ_BOOL ret;
    ret  = opj_sparse_array_int32_read(sa,
                                       sa_col, win_l_y0,
                                       sa_col + nb_cols, win_l_y1,
                                       dest + cas * 4 + 2 * 4 * win_l_y0,
                                       1, 2 * 4, OPJ_TRUE);
    assert(ret);
    ret = opj_sparse_array_int32_read(sa,
                                      sa_col, sn + win_h_y0,
                                      sa_col + nb_cols, sn + win_h_y1,
                                      dest + (1 - cas) * 4 + 2 * 4 * win_h_y0,
                                      1, 2 * 4, OPJ_TRUE);
    assert(ret);
    OPJ_UNUSED(ret);
}