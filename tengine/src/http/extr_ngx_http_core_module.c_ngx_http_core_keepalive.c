#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_6__ {scalar_t__ keepalive_timeout; scalar_t__ keepalive_header; } ;
typedef  TYPE_2__ ngx_http_core_loc_conf_t ;
struct TYPE_7__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_5__ {int nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_MSEC ; 
 scalar_t__ NGX_ERROR ; 
 void* ngx_parse_time (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_http_core_keepalive(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    ngx_str_t  *value;

    if (clcf->keepalive_timeout != NGX_CONF_UNSET_MSEC) {
        return "is duplicate";
    }

    value = cf->args->elts;

    clcf->keepalive_timeout = ngx_parse_time(&value[1], 0);

    if (clcf->keepalive_timeout == (ngx_msec_t) NGX_ERROR) {
        return "invalid value";
    }

    if (cf->args->nelts == 2) {
        return NGX_CONF_OK;
    }

    clcf->keepalive_header = ngx_parse_time(&value[2], 1);

    if (clcf->keepalive_header == (time_t) NGX_ERROR) {
        return "invalid value";
    }

    return NGX_CONF_OK;
}