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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  ngx_http_lua_body_filter_by_lua_env (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_pcre_malloc_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_pcre_malloc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_traceback ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_http_lua_body_filter_by_chunk(lua_State *L, ngx_http_request_t *r,
    ngx_chain_t *in)
{
    ngx_int_t        rc;
    u_char          *err_msg;
    size_t           len;
#if (NGX_PCRE)
    ngx_pool_t      *old_pool;
#endif

    dd("initialize nginx context in Lua VM, code chunk at stack top  sp = 1");
    ngx_http_lua_body_filter_by_lua_env(L, r, in);

#if (NGX_PCRE)
    /* XXX: work-around to nginx regex subsystem */
    old_pool = ngx_http_lua_pcre_malloc_init(r->pool);
#endif

    lua_pushcfunction(L, ngx_http_lua_traceback);
    lua_insert(L, 1);  /* put it under chunk and args */

    dd("protected call user code");
    rc = lua_pcall(L, 0, 1, 1);

    lua_remove(L, 1);  /* remove traceback function */

#if (NGX_PCRE)
    /* XXX: work-around to nginx regex subsystem */
    ngx_http_lua_pcre_malloc_done(old_pool);
#endif

    if (rc != 0) {

        /*  error occurred */
        err_msg = (u_char *) lua_tolstring(L, -1, &len);

        if (err_msg == NULL) {
            err_msg = (u_char *) "unknown reason";
            len = sizeof("unknown reason") - 1;
        }

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "failed to run body_filter_by_lua*: %*s", len, err_msg);

        lua_settop(L, 0);    /*  clear remaining elems on stack */

        return NGX_ERROR;
    }

    /* rc == 0 */

    rc = (ngx_int_t) lua_tointeger(L, -1);

    dd("got return value: %d", (int) rc);

    lua_settop(L, 0);

    if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return NGX_ERROR;
    }

    return NGX_OK;
}