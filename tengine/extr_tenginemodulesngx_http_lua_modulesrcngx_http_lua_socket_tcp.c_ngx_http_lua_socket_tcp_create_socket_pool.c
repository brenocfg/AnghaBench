#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_16__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_17__ {int backlog; int size; int /*<<< orphan*/  free; scalar_t__ key; int /*<<< orphan*/  cache; int /*<<< orphan*/  wait_connect_op; int /*<<< orphan*/  cache_connect_op; int /*<<< orphan*/  lua_vm; scalar_t__ connections; } ;
typedef  TYPE_4__ ngx_http_lua_socket_pool_t ;
struct TYPE_18__ {TYPE_4__* socket_pool; int /*<<< orphan*/  queue; } ;
typedef  TYPE_5__ ngx_http_lua_socket_pool_item_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 size_t ngx_align (int /*<<< orphan*/ ,int) ; 
 void* ngx_align_ptr (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * ngx_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int) ; 
 int /*<<< orphan*/  ngx_http_lua_get_lua_vm (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_udata_metatable_key ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_create_socket_pool(lua_State *L, ngx_http_request_t *r,
    ngx_str_t key, ngx_int_t pool_size, ngx_int_t backlog,
    ngx_http_lua_socket_pool_t **spool)
{
    u_char                              *p;
    size_t                               size, key_len;
    ngx_int_t                            i;
    ngx_http_lua_socket_pool_t          *sp;
    ngx_http_lua_socket_pool_item_t     *items;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket connection pool size: %i, backlog: %i",
                   pool_size, backlog);

    key_len = ngx_align(key.len + 1, sizeof(void *));

    size = sizeof(ngx_http_lua_socket_pool_t) - 1 + key_len
           + sizeof(ngx_http_lua_socket_pool_item_t) * pool_size;

    /* before calling this function, the Lua stack is:
     * -1 key
     * -2 pools
     */
    sp = lua_newuserdata(L, size);
    if (sp == NULL) {
        luaL_error(L, "no memory");
        return;
    }

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          pool_udata_metatable_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_setmetatable(L, -2);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket keepalive create connection pool for key"
                   " \"%V\"", &key);

    /* a new socket pool with metatable is push to the stack, so now we have:
     * -1 sp
     * -2 key
     * -3 pools
     *
     * it is time to set pools[key] to sp.
     */
    lua_rawset(L, -3);

    /* clean up the stack for consistency's sake */
    lua_pop(L, 1);

    sp->backlog = backlog;
    sp->size = pool_size;
    sp->connections = 0;
    sp->lua_vm = ngx_http_lua_get_lua_vm(r, NULL);

    ngx_queue_init(&sp->cache_connect_op);
    ngx_queue_init(&sp->wait_connect_op);
    ngx_queue_init(&sp->cache);
    ngx_queue_init(&sp->free);

    p = ngx_copy(sp->key, key.data, key.len);
    *p++ = '\0';

    items = (ngx_http_lua_socket_pool_item_t *) (sp->key + key_len);

    dd("items: %p", items);

    ngx_http_lua_assert((void *) items == ngx_align_ptr(items, sizeof(void *)));

    for (i = 0; i < pool_size; i++) {
        ngx_queue_insert_head(&sp->free, &items[i].queue);
        items[i].socket_pool = sp;
    }

    *spool = sp;
}