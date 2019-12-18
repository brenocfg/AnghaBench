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
struct TYPE_3__ {scalar_t__ win_l_x0; scalar_t__ win_l_x1; int win_h_x0; scalar_t__ win_h_x1; scalar_t__ cas; scalar_t__ wavelet; scalar_t__ sn; } ;
typedef  TYPE_1__ opj_v4dwt_t ;
typedef  int /*<<< orphan*/  opj_sparse_array_int32_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  OPJ_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_sparse_array_int32_read (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_v4dwt_interleave_partial_h(opj_v4dwt_t* dwt,
        opj_sparse_array_int32_t* sa,
        OPJ_UINT32 sa_line,
        OPJ_UINT32 remaining_height)
{
    OPJ_UINT32 i;
    for (i = 0; i < remaining_height; i++) {
        OPJ_BOOL ret;
        ret = opj_sparse_array_int32_read(sa,
                                          dwt->win_l_x0, sa_line + i,
                                          dwt->win_l_x1, sa_line + i + 1,
                                          /* Nasty cast from float* to int32* */
                                          (OPJ_INT32*)(dwt->wavelet + dwt->cas + 2 * dwt->win_l_x0) + i,
                                          8, 0, OPJ_TRUE);
        assert(ret);
        ret = opj_sparse_array_int32_read(sa,
                                          (OPJ_UINT32)dwt->sn + dwt->win_h_x0, sa_line + i,
                                          (OPJ_UINT32)dwt->sn + dwt->win_h_x1, sa_line + i + 1,
                                          /* Nasty cast from float* to int32* */
                                          (OPJ_INT32*)(dwt->wavelet + 1 - dwt->cas + 2 * dwt->win_h_x0) + i,
                                          8, 0, OPJ_TRUE);
        assert(ret);
        OPJ_UNUSED(ret);
    }
}