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
struct TYPE_8__ {size_t check_shm_size; } ;
typedef  TYPE_2__ ngx_http_upstream_check_main_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 TYPE_2__* ngx_http_conf_get_module_main_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 
 size_t ngx_parse_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_upstream_check_shm_size(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                            *value;
    ngx_http_upstream_check_main_conf_t  *ucmcf;

    ucmcf = ngx_http_conf_get_module_main_conf(cf,
                                               ngx_http_upstream_check_module);
    if (ucmcf->check_shm_size) {
        return "is duplicate";
    }

    value = cf->args->elts;

    ucmcf->check_shm_size = ngx_parse_size(&value[1]);
    if (ucmcf->check_shm_size == (size_t) NGX_ERROR) {
        return "invalid value";
    }

    return NGX_CONF_OK;
}