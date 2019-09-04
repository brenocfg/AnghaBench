#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {char* data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_16__ {TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_shm_zone_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/ * user_defined; } ;
typedef  TYPE_4__ ngx_http_reqstat_ctx_t ;
struct TYPE_18__ {int /*<<< orphan*/ * user_defined_str; } ;
typedef  TYPE_5__ ngx_http_reqstat_conf_t ;
struct TYPE_19__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_14__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_REQSTAT_USER ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 void* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 void* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_http_get_variable_index (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 TYPE_3__* ngx_shared_memory_add (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_reqstat_zone_add_indicator(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_int_t                         *i;
    ngx_str_t                         *value, *name;
    ngx_uint_t                         j;
    ngx_shm_zone_t                    *shm_zone;
    ngx_http_reqstat_ctx_t            *ctx;
    ngx_http_reqstat_conf_t           *rlcf;

    rlcf = conf;
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

    if (ctx->user_defined != NULL) {
        return "is duplicate";
    }

    if (cf->args->nelts > NGX_HTTP_REQSTAT_USER + 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "too many user defined variables");
        return NGX_CONF_ERROR;
    }

    ctx->user_defined = ngx_array_create(cf->pool, cf->args->nelts - 2,
                                         sizeof(ngx_int_t));
    if (ctx->user_defined == NULL) {
        return NGX_CONF_ERROR;
    }

    rlcf->user_defined_str = ngx_array_create(cf->pool, cf->args->nelts - 2,
                                              sizeof(ngx_str_t));
    if (rlcf->user_defined_str == NULL) {
        return NGX_CONF_ERROR;
    }

    for (j = 2; j < cf->args->nelts; j++) {
        if (value[j].data[0] == '$') {
            value[j].data++;
            value[j].len--;
        }

        name = ngx_array_push(rlcf->user_defined_str);
        name->len = value[j].len;
        name->data = value[j].data;

        i = ngx_array_push(ctx->user_defined);
        *i = ngx_http_get_variable_index(cf, &value[j]);
        if (*i == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "failed to obtain variable \"%V\"",
                               &value[j]);
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}