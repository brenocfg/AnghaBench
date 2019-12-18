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
typedef  size_t OPJ_SIZE_T ;
typedef  size_t OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD (size_t const*) ; 
 size_t PARALLEL_COLS_53 ; 
 int /*<<< orphan*/  STOREU (size_t*,int /*<<< orphan*/ ) ; 
 size_t VREG_INT_COUNT ; 

__attribute__((used)) static
void opj_idwt53_v_final_memcpy(OPJ_INT32* tiledp_col,
                               const OPJ_INT32* tmp,
                               OPJ_INT32 len,
                               OPJ_SIZE_T stride)
{
    OPJ_INT32 i;
    for (i = 0; i < len; ++i) {
        /* A memcpy(&tiledp_col[i * stride + 0],
                    &tmp[PARALLEL_COLS_53 * i + 0],
                    PARALLEL_COLS_53 * sizeof(OPJ_INT32))
           would do but would be a tiny bit slower.
           We can take here advantage of our knowledge of alignment */
        STOREU(&tiledp_col[(OPJ_SIZE_T)i * stride + 0],
               LOAD(&tmp[PARALLEL_COLS_53 * i + 0]));
        STOREU(&tiledp_col[(OPJ_SIZE_T)i * stride + VREG_INT_COUNT],
               LOAD(&tmp[PARALLEL_COLS_53 * i + VREG_INT_COUNT]));
    }
}