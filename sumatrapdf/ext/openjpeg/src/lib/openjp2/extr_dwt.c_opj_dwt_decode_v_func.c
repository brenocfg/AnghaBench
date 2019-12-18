#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tls_t ;
struct TYPE_5__ {int /*<<< orphan*/  mem; } ;
struct TYPE_4__ {size_t min_j; size_t max_j; TYPE_2__ v; scalar_t__ w; int /*<<< orphan*/ * tiledp; } ;
typedef  TYPE_1__ opj_dwd_decode_v_job_t ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_SIZE_T ;
typedef  size_t OPJ_INT32 ;

/* Variables and functions */
 size_t PARALLEL_COLS_53 ; 
 int /*<<< orphan*/  opj_aligned_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_idwt53_v (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void opj_dwt_decode_v_func(void* user_data, opj_tls_t* tls)
{
    OPJ_UINT32 j;
    opj_dwd_decode_v_job_t* job;
    (void)tls;

    job = (opj_dwd_decode_v_job_t*)user_data;
    for (j = job->min_j; j + PARALLEL_COLS_53 <= job->max_j;
            j += PARALLEL_COLS_53) {
        opj_idwt53_v(&job->v, &job->tiledp[j], (OPJ_SIZE_T)job->w,
                     PARALLEL_COLS_53);
    }
    if (j < job->max_j)
        opj_idwt53_v(&job->v, &job->tiledp[j], (OPJ_SIZE_T)job->w,
                     (OPJ_INT32)(job->max_j - j));

    opj_aligned_free(job->v.mem);
    opj_free(job);
}