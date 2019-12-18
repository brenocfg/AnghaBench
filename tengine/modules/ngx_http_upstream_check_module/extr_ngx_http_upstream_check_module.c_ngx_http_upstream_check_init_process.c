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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_check_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_cycle_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_add_timers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_init_process(ngx_cycle_t *cycle)
{
    ngx_http_upstream_check_main_conf_t *ucmcf;

    ucmcf = ngx_http_cycle_get_module_main_conf(cycle, ngx_http_upstream_check_module);
    if (ucmcf == NULL) {
        return NGX_OK;
    }

    return ngx_http_upstream_check_add_timers(cycle);
}