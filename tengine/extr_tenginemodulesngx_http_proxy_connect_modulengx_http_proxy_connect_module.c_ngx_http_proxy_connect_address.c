#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_20__ {TYPE_15__* addr; TYPE_4__* value; } ;
typedef  TYPE_3__ ngx_http_proxy_connect_address_t ;
struct TYPE_21__ {scalar_t__ lengths; } ;
typedef  TYPE_4__ ngx_http_complex_value_t ;
struct TYPE_22__ {TYPE_4__* complex_value; TYPE_2__* value; TYPE_6__* cf; } ;
typedef  TYPE_5__ ngx_http_compile_complex_value_t ;
struct TYPE_23__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_24__ {int offset; } ;
typedef  TYPE_7__ ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;
struct TYPE_18__ {TYPE_2__* elts; } ;
struct TYPE_17__ {TYPE_2__ name; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_3__* NGX_CONF_UNSET_PTR ; 
#define  NGX_DECLINED 129 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
#define  NGX_OK 128 
 int __ngx_parse_addr_port (int /*<<< orphan*/ ,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 scalar_t__ ngx_http_compile_complex_value (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

char *
ngx_http_proxy_connect_address(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    char  *p = conf;

    ngx_int_t                           rc;
    ngx_str_t                          *value;
    ngx_http_complex_value_t            cv;
    ngx_http_proxy_connect_address_t  **paddress, *address;
    ngx_http_compile_complex_value_t    ccv;

    paddress = (ngx_http_proxy_connect_address_t **) (p + cmd->offset);

    if (*paddress != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "off") == 0) {
        *paddress = NULL;
        return NGX_CONF_OK;
    }

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &cv;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    address = ngx_pcalloc(cf->pool, sizeof(ngx_http_proxy_connect_address_t));
    if (address == NULL) {
        return NGX_CONF_ERROR;
    }

    *paddress = address;

    if (cv.lengths) {
        address->value = ngx_palloc(cf->pool, sizeof(ngx_http_complex_value_t));
        if (address->value == NULL) {
            return NGX_CONF_ERROR;
        }

        *address->value = cv;

    } else {
        address->addr = ngx_palloc(cf->pool, sizeof(ngx_addr_t));
        if (address->addr == NULL) {
            return NGX_CONF_ERROR;
        }

        rc = __ngx_parse_addr_port(cf->pool, address->addr, value[1].data,
                                   value[1].len);

        switch (rc) {
        case NGX_OK:
            address->addr->name = value[1];
            break;

        case NGX_DECLINED:
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid address \"%V\"", &value[1]);
            /* fall through */

        default:
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}