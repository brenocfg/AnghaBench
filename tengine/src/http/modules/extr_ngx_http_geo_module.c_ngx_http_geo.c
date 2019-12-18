#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_22__ {int ranges; int proxy_recursive; scalar_t__ tree6; scalar_t__ tree; } ;
typedef  TYPE_3__ ngx_http_geo_conf_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/  pool; TYPE_1__* args; TYPE_3__* ctx; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_cidr_t ;
struct TYPE_20__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 char* ngx_http_geo_add_proxy (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* ngx_http_geo_cidr (TYPE_4__*,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ ngx_http_geo_cidr_value (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* ngx_http_geo_include (TYPE_4__*,TYPE_3__*,TYPE_2__*) ; 
 char* ngx_http_geo_range (TYPE_4__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_reset_pool (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_geo(ngx_conf_t *cf, ngx_command_t *dummy, void *conf)
{
    char                     *rv;
    ngx_str_t                *value;
    ngx_cidr_t                cidr;
    ngx_http_geo_conf_ctx_t  *ctx;

    ctx = cf->ctx;

    value = cf->args->elts;

    if (cf->args->nelts == 1) {

        if (ngx_strcmp(value[0].data, "ranges") == 0) {

            if (ctx->tree
#if (NGX_HAVE_INET6)
                || ctx->tree6
#endif
               )
            {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "the \"ranges\" directive must be "
                                   "the first directive inside \"geo\" block");
                goto failed;
            }

            ctx->ranges = 1;

            rv = NGX_CONF_OK;

            goto done;
        }

        else if (ngx_strcmp(value[0].data, "proxy_recursive") == 0) {
            ctx->proxy_recursive = 1;
            rv = NGX_CONF_OK;
            goto done;
        }
    }

    if (cf->args->nelts != 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid number of the geo parameters");
        goto failed;
    }

    if (ngx_strcmp(value[0].data, "include") == 0) {

        rv = ngx_http_geo_include(cf, ctx, &value[1]);

        goto done;

    } else if (ngx_strcmp(value[0].data, "proxy") == 0) {

        if (ngx_http_geo_cidr_value(cf, &value[1], &cidr) != NGX_OK) {
            goto failed;
        }

        rv = ngx_http_geo_add_proxy(cf, ctx, &cidr);

        goto done;
    }

    if (ctx->ranges) {
        rv = ngx_http_geo_range(cf, ctx, value);

    } else {
        rv = ngx_http_geo_cidr(cf, ctx, value);
    }

done:

    ngx_reset_pool(cf->pool);

    return rv;

failed:

    ngx_reset_pool(cf->pool);

    return NGX_CONF_ERROR;
}