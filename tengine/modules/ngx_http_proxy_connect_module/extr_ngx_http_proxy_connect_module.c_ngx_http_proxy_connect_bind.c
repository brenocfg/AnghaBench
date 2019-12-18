#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_19__ {int transparent; TYPE_14__* addr; TYPE_4__* value; } ;
typedef  TYPE_3__ ngx_http_proxy_connect_address_t ;
struct TYPE_20__ {scalar_t__ lengths; } ;
typedef  TYPE_4__ ngx_http_complex_value_t ;
struct TYPE_21__ {TYPE_4__* complex_value; TYPE_2__* value; TYPE_6__* cf; } ;
typedef  TYPE_5__ ngx_http_compile_complex_value_t ;
struct TYPE_22__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_23__ {int offset; } ;
typedef  TYPE_7__ ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;
struct TYPE_17__ {int nelts; TYPE_2__* elts; } ;
struct TYPE_16__ {TYPE_2__ name; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_3__* NGX_CONF_UNSET_PTR ; 
#define  NGX_DECLINED 129 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
#define  NGX_OK 128 
 int __ngx_parse_addr_port (int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_http_compile_complex_value (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

char *
ngx_http_proxy_connect_bind(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    char  *p = conf;

    ngx_int_t                           rc;
    ngx_str_t                          *value;
    ngx_http_complex_value_t            cv;
    ngx_http_proxy_connect_address_t  **plocal, *local;
    ngx_http_compile_complex_value_t    ccv;

    plocal = (ngx_http_proxy_connect_address_t **) (p + cmd->offset);

    if (*plocal != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (cf->args->nelts == 2 && ngx_strcmp(value[1].data, "off") == 0) {
        *plocal = NULL;
        return NGX_CONF_OK;
    }

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &cv;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    local = ngx_pcalloc(cf->pool, sizeof(ngx_http_proxy_connect_address_t));
    if (local == NULL) {
        return NGX_CONF_ERROR;
    }

    *plocal = local;

    if (cv.lengths) {
        local->value = ngx_palloc(cf->pool, sizeof(ngx_http_complex_value_t));
        if (local->value == NULL) {
            return NGX_CONF_ERROR;
        }

        *local->value = cv;

    } else {
        local->addr = ngx_palloc(cf->pool, sizeof(ngx_addr_t));
        if (local->addr == NULL) {
            return NGX_CONF_ERROR;
        }

        rc = __ngx_parse_addr_port(cf->pool, local->addr, value[1].data,
                                   value[1].len);

        switch (rc) {
        case NGX_OK:
            local->addr->name = value[1];
            break;

        case NGX_DECLINED:
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid address \"%V\"", &value[1]);
            /* fall through */

        default:
            return NGX_CONF_ERROR;
        }
    }

    if (cf->args->nelts > 2) {
        if (ngx_strcmp(value[2].data, "transparent") == 0) {
#if (NGX_HAVE_TRANSPARENT_PROXY)
            local->transparent = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "transparent proxying is not supported "
                               "on this platform, ignored");
#endif
        } else {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid parameter \"%V\"", &value[2]);
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}