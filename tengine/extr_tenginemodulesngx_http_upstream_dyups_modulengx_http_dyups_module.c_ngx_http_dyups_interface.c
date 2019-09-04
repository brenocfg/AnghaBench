#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enable; } ;
typedef  TYPE_1__ ngx_http_dyups_main_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_2__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 TYPE_2__* ngx_http_conf_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_dyups_interface_handler ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 

__attribute__((used)) static char *
ngx_http_dyups_interface(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t    *clcf;
    ngx_http_dyups_main_conf_t  *dmcf;

    dmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_dyups_module);
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_dyups_interface_handler;
    dmcf->enable = 1;

    return NGX_CONF_OK;
}