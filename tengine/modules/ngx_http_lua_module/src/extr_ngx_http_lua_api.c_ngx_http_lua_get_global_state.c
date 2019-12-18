#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lua; } ;
typedef  TYPE_1__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* ngx_http_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

lua_State *
ngx_http_lua_get_global_state(ngx_conf_t *cf)
{
    ngx_http_lua_main_conf_t *lmcf;

    lmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_lua_module);

    return lmcf->lua;
}