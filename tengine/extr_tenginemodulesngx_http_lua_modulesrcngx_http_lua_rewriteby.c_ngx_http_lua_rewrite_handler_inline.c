#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_2__ value; } ;
struct TYPE_15__ {scalar_t__ rewrite_chunkname; int /*<<< orphan*/  rewrite_src_key; TYPE_3__ rewrite_src; } ;
typedef  TYPE_5__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_cache_loadbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_rewrite_by_chunk (int /*<<< orphan*/ *,TYPE_4__*) ; 

ngx_int_t
ngx_http_lua_rewrite_handler_inline(ngx_http_request_t *r)
{
    lua_State                   *L;
    ngx_int_t                    rc;
    ngx_http_lua_loc_conf_t     *llcf;

    dd("rewrite by lua inline");

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);
    L = ngx_http_lua_get_lua_vm(r, NULL);

    /*  load Lua inline script (w/ cache) sp = 1 */
    rc = ngx_http_lua_cache_loadbuffer(r->connection->log, L,
                                       llcf->rewrite_src.value.data,
                                       llcf->rewrite_src.value.len,
                                       llcf->rewrite_src_key,
                                       (const char *)
                                       llcf->rewrite_chunkname);
    if (rc != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    return ngx_http_lua_rewrite_by_chunk(L, r);
}