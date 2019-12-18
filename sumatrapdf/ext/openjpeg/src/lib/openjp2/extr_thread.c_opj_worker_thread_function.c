#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * tp; } ;
typedef  TYPE_1__ opj_worker_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* job_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ opj_worker_thread_job_t ;
typedef  int /*<<< orphan*/  opj_tls_t ;
typedef  int /*<<< orphan*/  opj_thread_pool_t ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ OPJ_FALSE ; 
 scalar_t__ OPJ_TRUE ; 
 int /*<<< orphan*/  opj_free (TYPE_2__*) ; 
 TYPE_2__* opj_thread_pool_get_next_job (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_tls_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opj_tls_new () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opj_worker_thread_function(void* user_data)
{
    opj_worker_thread_t* worker_thread;
    opj_thread_pool_t* tp;
    opj_tls_t* tls;
    OPJ_BOOL job_finished = OPJ_FALSE;

    worker_thread = (opj_worker_thread_t*) user_data;
    tp = worker_thread->tp;
    tls = opj_tls_new();

    while (OPJ_TRUE) {
        opj_worker_thread_job_t* job = opj_thread_pool_get_next_job(tp, worker_thread,
                                       job_finished);
        if (job == NULL) {
            break;
        }

        if (job->job_fn) {
            job->job_fn(job->user_data, tls);
        }
        opj_free(job);
        job_finished = OPJ_TRUE;
    }

    opj_tls_destroy(tls);
}