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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_handler_pt ;
struct TYPE_5__ {TYPE_1__* phases; } ;
typedef  TYPE_2__ ngx_http_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_4__ {int /*<<< orphan*/  handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 size_t NGX_HTTP_LOG_PHASE ; 
 size_t NGX_HTTP_REWRITE_PHASE ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_http_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_next_input_body_filter ; 
 int /*<<< orphan*/  ngx_http_reqstat_init_handler ; 
 int /*<<< orphan*/  ngx_http_reqstat_input_body_filter ; 
 int /*<<< orphan*/  ngx_http_reqstat_log_flow ; 
 int /*<<< orphan*/  ngx_http_reqstat_log_handler ; 
 int /*<<< orphan*/  ngx_http_top_input_body_filter ; 
 int /*<<< orphan*/  ngx_http_write_filter_stat ; 

__attribute__((used)) static ngx_int_t
ngx_http_reqstat_init(ngx_conf_t *cf)
{
    ngx_http_handler_pt          *h;
    ngx_http_core_main_conf_t    *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_LOG_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_reqstat_log_handler;

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_REWRITE_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_reqstat_init_handler;

    ngx_http_next_input_body_filter = ngx_http_top_input_body_filter;
    ngx_http_top_input_body_filter = ngx_http_reqstat_input_body_filter;

    ngx_http_write_filter_stat = ngx_http_reqstat_log_flow;

    return NGX_OK;
}