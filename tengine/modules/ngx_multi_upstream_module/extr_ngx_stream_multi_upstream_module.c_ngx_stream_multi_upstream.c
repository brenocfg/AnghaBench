#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ init_upstream; } ;
struct TYPE_16__ {TYPE_2__ peer; } ;
typedef  TYPE_3__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_17__ {scalar_t__ original_init_upstream; scalar_t__ max_cached; } ;
typedef  TYPE_4__ ngx_stream_multi_upstream_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ ngx_command_t ;
struct TYPE_14__ {TYPE_5__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_stream_conf_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_multi_upstream_init ; 
 scalar_t__ ngx_stream_upstream_init_round_robin ; 
 int /*<<< orphan*/  ngx_stream_upstream_module ; 

__attribute__((used)) static char *
ngx_stream_multi_upstream(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_upstream_srv_conf_t          *uscf;
    ngx_stream_multi_upstream_srv_conf_t    *kcf = conf;

    ngx_int_t    n;
    ngx_str_t   *value;

    if (kcf->max_cached) {
        return "is duplicate";
    }

    /* read options */

    value = cf->args->elts;

    n = ngx_atoi(value[1].data, value[1].len);

    if (n == NGX_ERROR || n == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid value \"%V\" in \"%V\" directive",
                           &value[1], &cmd->name);
        return NGX_CONF_ERROR;
    }

    kcf->max_cached = n;

    uscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_upstream_module);

    kcf->original_init_upstream = uscf->peer.init_upstream
                                  ? uscf->peer.init_upstream
                                  : ngx_stream_upstream_init_round_robin;

    uscf->peer.init_upstream = ngx_stream_multi_upstream_init;

    return NGX_CONF_OK;
}