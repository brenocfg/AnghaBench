#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tls; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ opj_thread_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPJWTS_OK ; 
 scalar_t__ opj_calloc (int,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_mutex_create () ; 
 int /*<<< orphan*/  opj_thread_pool_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_thread_pool_setup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  opj_tls_new () ; 

opj_thread_pool_t* opj_thread_pool_create(int num_threads)
{
    opj_thread_pool_t* tp;

    tp = (opj_thread_pool_t*) opj_calloc(1, sizeof(opj_thread_pool_t));
    if (!tp) {
        return NULL;
    }
    tp->state = OPJWTS_OK;

    if (num_threads <= 0) {
        tp->tls = opj_tls_new();
        if (!tp->tls) {
            opj_free(tp);
            tp = NULL;
        }
        return tp;
    }

    tp->mutex = opj_mutex_create();
    if (!tp->mutex) {
        opj_free(tp);
        return NULL;
    }
    if (!opj_thread_pool_setup(tp, num_threads)) {
        opj_thread_pool_destroy(tp);
        return NULL;
    }
    return tp;
}