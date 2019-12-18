#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_13__ {TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_shm_zone_t ;
typedef  int ngx_int_t ;
struct TYPE_14__ {int recycle_rate; } ;
typedef  TYPE_4__ ngx_http_reqstat_ctx_t ;
struct TYPE_15__ {TYPE_1__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_11__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 TYPE_3__* ngx_shared_memory_add (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_reqstat_zone_recycle(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_int_t                          rate, scale;
    ngx_str_t                         *value;
    ngx_shm_zone_t                    *shm_zone;
    ngx_http_reqstat_ctx_t            *ctx;

    value = cf->args->elts;

    shm_zone = ngx_shared_memory_add(cf, &value[1], 0,
                                     &ngx_http_reqstat_module);
    if (shm_zone == NULL) {
        return NGX_CONF_ERROR;
    }

    if (shm_zone->data == NULL) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "zone \"%V\" should be defined first",
                           &value[1]);
        return NGX_CONF_ERROR;
    }

    ctx = shm_zone->data;

    rate = ngx_atoi(value[2].data, value[2].len);
    if (rate == NGX_ERROR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid threshold");
        return NGX_CONF_ERROR;
    }

    scale = ngx_atoi(value[3].data, value[3].len);
    if (scale == NGX_ERROR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid scale");
        return NGX_CONF_ERROR;
    }

    ctx->recycle_rate = rate * 1000 / scale;

    return NGX_CONF_OK;
}