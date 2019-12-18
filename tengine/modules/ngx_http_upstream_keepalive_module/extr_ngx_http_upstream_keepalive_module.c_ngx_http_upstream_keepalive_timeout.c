#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_8__ {scalar_t__ keepalive_timeout; } ;
typedef  TYPE_2__ ngx_http_upstream_keepalive_srv_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_MSEC ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/ * ngx_http_conf_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_keepalive_module ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 scalar_t__ ngx_parse_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_upstream_keepalive_timeout(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_http_upstream_srv_conf_t  *uscf;
    ngx_http_upstream_keepalive_srv_conf_t  *kcf;

    ngx_str_t   *value;
    ngx_msec_t   timeout;

    uscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_upstream_module);

    kcf = ngx_http_conf_upstream_srv_conf(uscf,
                                          ngx_http_upstream_keepalive_module);

    if (kcf->keepalive_timeout != NGX_CONF_UNSET_MSEC) {
        return "is duplicate";
    }

    value = cf->args->elts;

    timeout = ngx_parse_time(&value[1], 0);
    if (timeout == (ngx_msec_t) NGX_ERROR) {
        return "invalid value";
    }

    kcf->keepalive_timeout = timeout;

    return NGX_CONF_OK;
}