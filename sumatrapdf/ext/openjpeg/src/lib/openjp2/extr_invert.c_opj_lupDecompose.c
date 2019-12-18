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
typedef  int OPJ_UINT32 ;
typedef  double OPJ_FLOAT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  memcpy (double*,double*,int) ; 

__attribute__((used)) static OPJ_BOOL opj_lupDecompose(OPJ_FLOAT32 * matrix,
                                 OPJ_UINT32 * permutations,
                                 OPJ_FLOAT32 * p_swap_area,
                                 OPJ_UINT32 nb_compo)
{
    OPJ_UINT32 * tmpPermutations = permutations;
    OPJ_UINT32 * dstPermutations;
    OPJ_UINT32 k2 = 0, t;
    OPJ_FLOAT32 temp;
    OPJ_UINT32 i, j, k;
    OPJ_FLOAT32 p;
    OPJ_UINT32 lLastColum = nb_compo - 1;
    OPJ_UINT32 lSwapSize = nb_compo * (OPJ_UINT32)sizeof(OPJ_FLOAT32);
    OPJ_FLOAT32 * lTmpMatrix = matrix;
    OPJ_FLOAT32 * lColumnMatrix, * lDestMatrix;
    OPJ_UINT32 offset = 1;
    OPJ_UINT32 lStride = nb_compo - 1;

    /*initialize permutations */
    for (i = 0; i < nb_compo; ++i) {
        *tmpPermutations++ = i;
    }
    /* now make a pivot with column switch */
    tmpPermutations = permutations;
    for (k = 0; k < lLastColum; ++k) {
        p = 0.0;

        /* take the middle element */
        lColumnMatrix = lTmpMatrix + k;

        /* make permutation with the biggest value in the column */
        for (i = k; i < nb_compo; ++i) {
            temp = ((*lColumnMatrix > 0) ? *lColumnMatrix : -(*lColumnMatrix));
            if (temp > p) {
                p = temp;
                k2 = i;
            }
            /* next line */
            lColumnMatrix += nb_compo;
        }

        /* a whole rest of 0 -> non singular */
        if (p == 0.0) {
            return OPJ_FALSE;
        }

        /* should we permute ? */
        if (k2 != k) {
            /*exchange of line */
            /* k2 > k */
            dstPermutations = tmpPermutations + k2 - k;
            /* swap indices */
            t = *tmpPermutations;
            *tmpPermutations = *dstPermutations;
            *dstPermutations = t;

            /* and swap entire line. */
            lColumnMatrix = lTmpMatrix + (k2 - k) * nb_compo;
            memcpy(p_swap_area, lColumnMatrix, lSwapSize);
            memcpy(lColumnMatrix, lTmpMatrix, lSwapSize);
            memcpy(lTmpMatrix, p_swap_area, lSwapSize);
        }

        /* now update data in the rest of the line and line after */
        lDestMatrix = lTmpMatrix + k;
        lColumnMatrix = lDestMatrix + nb_compo;
        /* take the middle element */
        temp = *(lDestMatrix++);

        /* now compute up data (i.e. coeff up of the diagonal). */
        for (i = offset; i < nb_compo; ++i)  {
            /*lColumnMatrix; */
            /* divide the lower column elements by the diagonal value */

            /* matrix[i][k] /= matrix[k][k]; */
            /* p = matrix[i][k] */
            p = *lColumnMatrix / temp;
            *(lColumnMatrix++) = p;

            for (j = /* k + 1 */ offset; j < nb_compo; ++j) {
                /* matrix[i][j] -= matrix[i][k] * matrix[k][j]; */
                *(lColumnMatrix++) -= p * (*(lDestMatrix++));
            }
            /* come back to the k+1th element */
            lDestMatrix -= lStride;
            /* go to kth element of the next line */
            lColumnMatrix += k;
        }

        /* offset is now k+2 */
        ++offset;
        /* 1 element less for stride */
        --lStride;
        /* next line */
        lTmpMatrix += nb_compo;
        /* next permutation element */
        ++tmpPermutations;
    }
    return OPJ_TRUE;
}