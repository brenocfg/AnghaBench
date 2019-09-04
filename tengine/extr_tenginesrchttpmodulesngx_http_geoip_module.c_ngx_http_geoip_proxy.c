#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_7__ {int /*<<< orphan*/ * proxies; } ;
typedef  TYPE_2__ ngx_http_geoip_conf_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_cidr_t ;
struct TYPE_6__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_geoip_cidr_value (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_geoip_proxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_geoip_conf_t  *gcf = conf;

    ngx_str_t   *value;
    ngx_cidr_t  cidr, *c;

    value = cf->args->elts;

    if (ngx_http_geoip_cidr_value(cf, &value[1], &cidr) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (gcf->proxies == NULL) {
        gcf->proxies = ngx_array_create(cf->pool, 4, sizeof(ngx_cidr_t));
        if (gcf->proxies == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    c = ngx_array_push(gcf->proxies);
    if (c == NULL) {
        return NGX_CONF_ERROR;
    }

    *c = cidr;

    return NGX_CONF_OK;
}