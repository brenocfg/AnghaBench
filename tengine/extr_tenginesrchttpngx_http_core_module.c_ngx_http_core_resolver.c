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
struct TYPE_7__ {int /*<<< orphan*/ * resolver; } ;
typedef  TYPE_2__ ngx_http_core_loc_conf_t ;
struct TYPE_8__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * ngx_resolver_create (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static char *
ngx_http_core_resolver(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf = conf;

    ngx_str_t  *value;

    if (clcf->resolver) {
        return "is duplicate";
    }

    value = cf->args->elts;

    clcf->resolver = ngx_resolver_create(cf, &value[1], cf->args->nelts - 1);
    if (clcf->resolver == NULL) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}