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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_lua_add_package_preload (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_fake_delayed_load_preload ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_fake_delayed_load_init(ngx_conf_t *cf)
{
    ngx_http_lua_add_package_preload(cf, "ngx.delayed_load",
                                     ngx_http_lua_fake_delayed_load_preload);
    return NGX_OK;
}