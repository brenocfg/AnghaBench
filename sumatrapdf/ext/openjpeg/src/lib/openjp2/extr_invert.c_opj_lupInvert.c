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
typedef  size_t OPJ_UINT32 ;
typedef  double OPJ_FLOAT32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  opj_lupSolve (double*,double*,double*,size_t*,size_t,double*) ; 

__attribute__((used)) static void opj_lupInvert(OPJ_FLOAT32 * pSrcMatrix,
                          OPJ_FLOAT32 * pDestMatrix,
                          OPJ_UINT32 nb_compo,
                          OPJ_UINT32 * pPermutations,
                          OPJ_FLOAT32 * p_src_temp,
                          OPJ_FLOAT32 * p_dest_temp,
                          OPJ_FLOAT32 * p_swap_area)
{
    OPJ_UINT32 j, i;
    OPJ_FLOAT32 * lCurrentPtr;
    OPJ_FLOAT32 * lLineMatrix = pDestMatrix;
    OPJ_UINT32 lSwapSize = nb_compo * (OPJ_UINT32)sizeof(OPJ_FLOAT32);

    for (j = 0; j < nb_compo; ++j) {
        lCurrentPtr = lLineMatrix++;
        memset(p_src_temp, 0, lSwapSize);
        p_src_temp[j] = 1.0;
        opj_lupSolve(p_dest_temp, pSrcMatrix, p_src_temp, pPermutations, nb_compo,
                     p_swap_area);

        for (i = 0; i < nb_compo; ++i) {
            *(lCurrentPtr) = p_dest_temp[i];
            lCurrentPtr += nb_compo;
        }
    }
}