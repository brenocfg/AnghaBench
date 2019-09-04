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
typedef  int /*<<< orphan*/  ngx_listening_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

ngx_int_t
ngx_clone_listening(ngx_cycle_t *cycle, ngx_listening_t *ls)
{
#if (NGX_HAVE_REUSEPORT)

    ngx_int_t         n;
    ngx_core_conf_t  *ccf;
    ngx_listening_t   ols;

    if (!ls->reuseport || ls->worker != 0) {
        return NGX_OK;
    }

    ols = *ls;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    for (n = 1; n < ccf->worker_processes; n++) {

        /* create a socket for each worker process */

        ls = ngx_array_push(&cycle->listening);
        if (ls == NULL) {
            return NGX_ERROR;
        }

        *ls = ols;
        ls->worker = n;
    }

#endif

    return NGX_OK;
}