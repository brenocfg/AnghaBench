#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_thread_pool_t ;
struct TYPE_5__ {size_t nelts; int /*<<< orphan*/ ** elts; } ;
struct TYPE_6__ {TYPE_1__ pools; } ;
typedef  TYPE_2__ ngx_thread_pool_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_3__ ngx_cycle_t ;

/* Variables and functions */
 scalar_t__ NGX_PROCESS_SINGLE ; 
 scalar_t__ NGX_PROCESS_WORKER ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_process ; 
 int /*<<< orphan*/  ngx_thread_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_thread_pool_module ; 

__attribute__((used)) static void
ngx_thread_pool_exit_worker(ngx_cycle_t *cycle)
{
    ngx_uint_t                i;
    ngx_thread_pool_t       **tpp;
    ngx_thread_pool_conf_t   *tcf;

    if (ngx_process != NGX_PROCESS_WORKER
        && ngx_process != NGX_PROCESS_SINGLE)
    {
        return;
    }

    tcf = (ngx_thread_pool_conf_t *) ngx_get_conf(cycle->conf_ctx,
                                                  ngx_thread_pool_module);

    if (tcf == NULL) {
        return;
    }

    tpp = tcf->pools.elts;

    for (i = 0; i < tcf->pools.nelts; i++) {
        ngx_thread_pool_destroy(tpp[i]);
    }
}