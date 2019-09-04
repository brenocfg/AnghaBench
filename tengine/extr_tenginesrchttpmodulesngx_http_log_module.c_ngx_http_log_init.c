#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {TYPE_4__* elts; } ;
struct TYPE_12__ {TYPE_1__ formats; scalar_t__ combined_used; } ;
typedef  TYPE_3__ ngx_http_log_main_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  ops; } ;
typedef  TYPE_4__ ngx_http_log_fmt_t ;
typedef  int /*<<< orphan*/  ngx_http_handler_pt ;
struct TYPE_14__ {TYPE_2__* phases; } ;
typedef  TYPE_5__ ngx_http_core_main_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_11__ {int /*<<< orphan*/  handlers; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_LOG_PHASE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 void* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_combined_fmt ; 
 void* ngx_http_conf_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 scalar_t__ ngx_http_log_compile_format (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_log_handler ; 
 int /*<<< orphan*/  ngx_http_log_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_log_init(ngx_conf_t *cf)
{
    ngx_str_t                  *value;
    ngx_array_t                 a;
    ngx_http_handler_pt        *h;
    ngx_http_log_fmt_t         *fmt;
    ngx_http_log_main_conf_t   *lmcf;
    ngx_http_core_main_conf_t  *cmcf;

    lmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_log_module);

    if (lmcf->combined_used) {
        if (ngx_array_init(&a, cf->pool, 1, sizeof(ngx_str_t)) != NGX_OK) {
            return NGX_ERROR;
        }

        value = ngx_array_push(&a);
        if (value == NULL) {
            return NGX_ERROR;
        }

        *value = ngx_http_combined_fmt;
        fmt = lmcf->formats.elts;

        if (ngx_http_log_compile_format(cf, NULL, fmt->ops, &a, 0)
            != NGX_CONF_OK)
        {
            return NGX_ERROR;
        }
    }

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_LOG_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_log_handler;

    return NGX_OK;
}