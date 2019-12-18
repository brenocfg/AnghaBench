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
struct TYPE_6__ {int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ ngx_http_dyups_srv_conf_t ;
struct TYPE_5__ {size_t nelts; TYPE_2__* elts; } ;
struct TYPE_7__ {TYPE_1__ dy_upstreams; } ;
typedef  TYPE_3__ ngx_http_dyups_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_cycle ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_http_cycle_get_module_main_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 

__attribute__((used)) static void
ngx_http_dyups_exit_process(ngx_cycle_t *cycle)
{
    ngx_uint_t                   i;
    ngx_http_dyups_srv_conf_t   *duscfs, *duscf;
    ngx_http_dyups_main_conf_t  *dumcf;

    dumcf = ngx_http_cycle_get_module_main_conf(ngx_cycle,
                                                ngx_http_dyups_module);
    if (!dumcf) {
        return;
    }

    duscfs = dumcf->dy_upstreams.elts;
    for (i = 0; i < dumcf->dy_upstreams.nelts; i++) {

        duscf = &duscfs[i];

        if (duscf->pool) {
            ngx_destroy_pool(duscf->pool);
            duscf->pool = NULL;
        }
    }
}