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
struct TYPE_3__ {int numresolutions; scalar_t__ qmfbid; scalar_t__ qntsty; int /*<<< orphan*/ * stepsizes; } ;
typedef  TYPE_1__ opj_tccp_t ;
typedef  int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int OPJ_FLOAT64 ;

/* Variables and functions */
 scalar_t__ J2K_CCP_QNTSTY_NOQNT ; 
 scalar_t__ floor (int) ; 
 int /*<<< orphan*/  opj_dwt_encode_stepsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int** opj_dwt_norms_real ; 

void opj_dwt_calc_explicit_stepsizes(opj_tccp_t * tccp, OPJ_UINT32 prec)
{
    OPJ_UINT32 numbands, bandno;
    numbands = 3 * tccp->numresolutions - 2;
    for (bandno = 0; bandno < numbands; bandno++) {
        OPJ_FLOAT64 stepsize;
        OPJ_UINT32 resno, level, orient, gain;

        resno = (bandno == 0) ? 0 : ((bandno - 1) / 3 + 1);
        orient = (bandno == 0) ? 0 : ((bandno - 1) % 3 + 1);
        level = tccp->numresolutions - 1 - resno;
        gain = (tccp->qmfbid == 0) ? 0 : ((orient == 0) ? 0 : (((orient == 1) ||
                                          (orient == 2)) ? 1 : 2));
        if (tccp->qntsty == J2K_CCP_QNTSTY_NOQNT) {
            stepsize = 1.0;
        } else {
            OPJ_FLOAT64 norm = opj_dwt_norms_real[orient][level];
            stepsize = (1 << (gain)) / norm;
        }
        opj_dwt_encode_stepsize((OPJ_INT32) floor(stepsize * 8192.0),
                                (OPJ_INT32)(prec + gain), &tccp->stepsizes[bandno]);
    }
}