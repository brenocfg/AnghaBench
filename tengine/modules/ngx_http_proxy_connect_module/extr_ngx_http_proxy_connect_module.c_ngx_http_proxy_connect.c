#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int accept_connect; } ;
typedef  TYPE_1__ ngx_http_proxy_connect_loc_conf_t ;
struct TYPE_4__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_2__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 void* ngx_http_conf_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 

__attribute__((used)) static char *
ngx_http_proxy_connect(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t            *clcf;
    ngx_http_proxy_connect_loc_conf_t   *pclcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_proxy_connect_handler;

    pclcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_proxy_connect_module);
    pclcf->accept_connect = 1;

    return NGX_CONF_OK;
}