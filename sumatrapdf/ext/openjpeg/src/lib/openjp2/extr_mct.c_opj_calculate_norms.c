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
typedef  scalar_t__ OPJ_FLOAT64 ;
typedef  int OPJ_FLOAT32 ;

/* Variables and functions */
 scalar_t__ sqrt (scalar_t__) ; 

void opj_calculate_norms(OPJ_FLOAT64 * pNorms,
                         OPJ_UINT32 pNbComps,
                         OPJ_FLOAT32 * pMatrix)
{
    OPJ_UINT32 i, j, lIndex;
    OPJ_FLOAT32 lCurrentValue;
    OPJ_FLOAT64 * lNorms = (OPJ_FLOAT64 *) pNorms;
    OPJ_FLOAT32 * lMatrix = (OPJ_FLOAT32 *) pMatrix;

    for (i = 0; i < pNbComps; ++i) {
        lNorms[i] = 0;
        lIndex = i;

        for (j = 0; j < pNbComps; ++j) {
            lCurrentValue = lMatrix[lIndex];
            lIndex += pNbComps;
            lNorms[i] += lCurrentValue * lCurrentValue;
        }
        lNorms[i] = sqrt(lNorms[i]);
    }
}