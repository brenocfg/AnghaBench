#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {scalar_t__ pos; scalar_t__ last; scalar_t__ start; } ;
struct TYPE_10__ {TYPE_1__ buffer; TYPE_4__* buf_in; TYPE_4__* bufs_in; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_11__ {TYPE_4__* free_recv_bufs; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
struct TYPE_12__ {TYPE_5__* buf; struct TYPE_12__* next; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_13__ {size_t last; size_t pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_socket_tcp_receive_done (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_push_input_data(ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx, ngx_http_lua_socket_tcp_upstream_t *u,
    lua_State *L)
{
    ngx_chain_t             *cl;
    ngx_chain_t            **ll;
#if (DDEBUG) || (NGX_DTRACE)
    size_t                   size = 0;
#endif
    size_t                   chunk_size;
    ngx_buf_t               *b;
    size_t                   nbufs;
    luaL_Buffer              luabuf;

    dd("bufs_in: %p, buf_in: %p", u->bufs_in, u->buf_in);

    nbufs = 0;
    ll = NULL;

    luaL_buffinit(L, &luabuf);

    for (cl = u->bufs_in; cl; cl = cl->next) {
        b = cl->buf;
        chunk_size = b->last - b->pos;

        dd("copying input data chunk from %p: \"%.*s\"", cl,
           (int) chunk_size, b->pos);

        luaL_addlstring(&luabuf, (char *) b->pos, chunk_size);

        if (cl->next) {
            ll = &cl->next;
        }

#if (DDEBUG) || (NGX_DTRACE)
        size += chunk_size;
#endif

        nbufs++;
    }

    luaL_pushresult(&luabuf);

#if (DDEBUG)
    dd("size: %d, nbufs: %d", (int) size, (int) nbufs);
#endif

#if (NGX_DTRACE)
    ngx_http_lua_probe_socket_tcp_receive_done(r, u,
                                               (u_char *) lua_tostring(L, -1),
                                               size);
#endif

    if (nbufs > 1 && ll) {
        dd("recycle buffers: %d", (int) (nbufs - 1));

        *ll = ctx->free_recv_bufs;
        ctx->free_recv_bufs = u->bufs_in;
        u->bufs_in = u->buf_in;
    }

    if (u->buffer.pos == u->buffer.last) {
        dd("resetting u->buffer pos & last");
        u->buffer.pos = u->buffer.start;
        u->buffer.last = u->buffer.start;
    }

    if (u->bufs_in) {
        u->buf_in->buf->last = u->buffer.pos;
        u->buf_in->buf->pos = u->buffer.pos;
    }

    return NGX_OK;
}