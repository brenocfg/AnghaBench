#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sn; scalar_t__ dn; scalar_t__* mem; scalar_t__ cas; } ;
typedef  TYPE_1__ opj_dwt_t ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */
 scalar_t__ PARALLEL_COLS_53 ; 
 int /*<<< orphan*/  opj_dwt_decode_1 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  opj_dwt_interleave_v (TYPE_1__ const*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_idwt3_v_cas0 (scalar_t__*,scalar_t__ const,scalar_t__ const,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_idwt3_v_cas1 (scalar_t__*,scalar_t__ const,scalar_t__ const,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_idwt53_v_cas0_mcols_SSE2_OR_AVX2 (scalar_t__*,scalar_t__ const,scalar_t__ const,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_idwt53_v_cas1_mcols_SSE2_OR_AVX2 (scalar_t__*,scalar_t__ const,scalar_t__ const,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void opj_idwt53_v(const opj_dwt_t *dwt,
                         OPJ_INT32* tiledp_col,
                         OPJ_SIZE_T stride,
                         OPJ_INT32 nb_cols)
{
#ifdef STANDARD_SLOW_VERSION
    /* For documentation purpose */
    OPJ_INT32 k, c;
    for (c = 0; c < nb_cols; c ++) {
        opj_dwt_interleave_v(dwt, tiledp_col + c, stride);
        opj_dwt_decode_1(dwt);
        for (k = 0; k < dwt->sn + dwt->dn; ++k) {
            tiledp_col[c + k * stride] = dwt->mem[k];
        }
    }
#else
    const OPJ_INT32 sn = dwt->sn;
    const OPJ_INT32 len = sn + dwt->dn;
    if (dwt->cas == 0) {
        /* If len == 1, unmodified value */

#if (defined(__SSE2__) || defined(__AVX2__))
        if (len > 1 && nb_cols == PARALLEL_COLS_53) {
            /* Same as below general case, except that thanks to SSE2/AVX2 */
            /* we can efficently process 8/16 columns in parallel */
            opj_idwt53_v_cas0_mcols_SSE2_OR_AVX2(dwt->mem, sn, len, tiledp_col, stride);
            return;
        }
#endif
        if (len > 1) {
            OPJ_INT32 c;
            for (c = 0; c < nb_cols; c++, tiledp_col++) {
                opj_idwt3_v_cas0(dwt->mem, sn, len, tiledp_col, stride);
            }
            return;
        }
    } else {
        if (len == 1) {
            OPJ_INT32 c;
            for (c = 0; c < nb_cols; c++, tiledp_col++) {
                tiledp_col[0] /= 2;
            }
            return;
        }

        if (len == 2) {
            OPJ_INT32 c;
            OPJ_INT32* out = dwt->mem;
            for (c = 0; c < nb_cols; c++, tiledp_col++) {
                OPJ_INT32 i;
                const OPJ_INT32* in_even = &tiledp_col[(OPJ_SIZE_T)sn * stride];
                const OPJ_INT32* in_odd = &tiledp_col[0];

                out[1] = in_odd[0] - ((in_even[0] + 1) >> 1);
                out[0] = in_even[0] + out[1];

                for (i = 0; i < len; ++i) {
                    tiledp_col[(OPJ_SIZE_T)i * stride] = out[i];
                }
            }

            return;
        }

#if (defined(__SSE2__) || defined(__AVX2__))
        if (len > 2 && nb_cols == PARALLEL_COLS_53) {
            /* Same as below general case, except that thanks to SSE2/AVX2 */
            /* we can efficently process 8/16 columns in parallel */
            opj_idwt53_v_cas1_mcols_SSE2_OR_AVX2(dwt->mem, sn, len, tiledp_col, stride);
            return;
        }
#endif
        if (len > 2) {
            OPJ_INT32 c;
            for (c = 0; c < nb_cols; c++, tiledp_col++) {
                opj_idwt3_v_cas1(dwt->mem, sn, len, tiledp_col, stride);
            }
            return;
        }
    }
#endif
}