#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  pool; TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_17__ {TYPE_6__* buf_in; TYPE_6__* bufs_in; TYPE_1__* conf; } ;
typedef  TYPE_4__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_18__ {int /*<<< orphan*/  free_recv_bufs; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_19__ {struct TYPE_19__* next; TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_20__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;
struct TYPE_14__ {size_t buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  dd (char*,TYPE_6__*,...) ; 
 scalar_t__ ngx_copy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_lua_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static ngx_int_t ngx_http_lua_socket_insert_buffer(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, u_char *pat, size_t prefix)
{
    ngx_chain_t             *cl, *new_cl, **ll;
    ngx_http_lua_ctx_t      *ctx;
    size_t                   size;
    ngx_buf_t               *b;

    if (prefix <= u->conf->buffer_size) {
        size = u->conf->buffer_size;

    } else {
        size = prefix;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    new_cl = ngx_http_lua_chain_get_free_buf(r->connection->log, r->pool,
                                             &ctx->free_recv_bufs,
                                             size);

    if (new_cl == NULL) {
        return NGX_ERROR;
    }

    b = new_cl->buf;

    b->last = ngx_copy(b->last, pat, prefix);

    dd("copy resumed data to %p: %d: \"%.*s\"",
       new_cl, (int) (b->last - b->pos), (int) (b->last - b->pos), b->pos);

    dd("before resuming data: bufs_in %p, buf_in %p, buf_in next %p",
       u->bufs_in, u->buf_in, u->buf_in->next);

    ll = &u->bufs_in;
    for (cl = u->bufs_in; cl->next; cl = cl->next) {
        ll = &cl->next;
    }

    *ll = new_cl;
    new_cl->next = u->buf_in;

    dd("after resuming data: bufs_in %p, buf_in %p, buf_in next %p",
       u->bufs_in, u->buf_in, u->buf_in->next);

#if (DDEBUG)
    for (cl = u->bufs_in; cl; cl = cl->next) {
        b = cl->buf;

        dd("result buf after resuming data: %p: %.*s", cl,
           (int) ngx_buf_size(b), b->pos);
    }
#endif

    return NGX_OK;
}