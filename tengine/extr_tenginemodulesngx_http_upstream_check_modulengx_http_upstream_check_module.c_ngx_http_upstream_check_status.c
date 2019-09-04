#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/ * format; } ;
typedef  TYPE_2__ ngx_http_upstream_check_loc_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_11__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {int nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* ngx_http_conf_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/ * ngx_http_get_check_status_format_conf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 
 int /*<<< orphan*/  ngx_http_upstream_check_status_handler ; 

__attribute__((used)) static char *
ngx_http_upstream_check_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                           *value;
    ngx_http_core_loc_conf_t            *clcf;
    ngx_http_upstream_check_loc_conf_t  *uclcf;

    value = cf->args->elts;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    clcf->handler = ngx_http_upstream_check_status_handler;

    if (cf->args->nelts == 2) {
        uclcf = ngx_http_conf_get_module_loc_conf(cf,
                                              ngx_http_upstream_check_module);

        uclcf->format = ngx_http_get_check_status_format_conf(&value[1]);
        if (uclcf->format == NULL) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid check format \"%V\"", &value[1]);

            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}