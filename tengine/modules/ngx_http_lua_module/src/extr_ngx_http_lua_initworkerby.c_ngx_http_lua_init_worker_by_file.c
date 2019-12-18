#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_5__ {TYPE_1__ init_worker_src; } ;
typedef  TYPE_2__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_loadfile (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ngx_http_lua_do_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_report (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

ngx_int_t
ngx_http_lua_init_worker_by_file(ngx_log_t *log, ngx_http_lua_main_conf_t *lmcf,
    lua_State *L)
{
    int         status;

    status = luaL_loadfile(L, (char *) lmcf->init_worker_src.data)
             || ngx_http_lua_do_call(log, L);

    return ngx_http_lua_report(log, L, status, "init_worker_by_lua_file");
}