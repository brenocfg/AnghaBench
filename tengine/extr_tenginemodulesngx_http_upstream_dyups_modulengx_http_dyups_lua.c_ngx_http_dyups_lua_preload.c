#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_dyups_lua_register ; 
 scalar_t__ ngx_http_lua_add_package_preload (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_dyups_lua_preload(ngx_conf_t *cf)
{
    if (ngx_http_lua_add_package_preload(cf, "ngx.dyups",
                                         ngx_http_dyups_lua_register)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}