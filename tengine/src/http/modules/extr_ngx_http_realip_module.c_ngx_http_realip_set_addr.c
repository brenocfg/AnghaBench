#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_13__ {int /*<<< orphan*/  handler; TYPE_4__* data; } ;
typedef  TYPE_2__ ngx_pool_cleanup_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {TYPE_5__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {TYPE_1__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_5__* connection; } ;
typedef  TYPE_4__ ngx_http_realip_ctx_t ;
struct TYPE_16__ {TYPE_1__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_17__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_6__ ngx_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_http_realip_cleanup ; 
 int /*<<< orphan*/  ngx_http_realip_module ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int) ; 
 size_t ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_realip_set_addr(ngx_http_request_t *r, ngx_addr_t *addr)
{
    size_t                  len;
    u_char                 *p;
    u_char                  text[NGX_SOCKADDR_STRLEN];
    ngx_connection_t       *c;
    ngx_pool_cleanup_t     *cln;
    ngx_http_realip_ctx_t  *ctx;

    cln = ngx_pool_cleanup_add(r->pool, sizeof(ngx_http_realip_ctx_t));
    if (cln == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ctx = cln->data;

    c = r->connection;

    len = ngx_sock_ntop(addr->sockaddr, addr->socklen, text,
                        NGX_SOCKADDR_STRLEN, 0);
    if (len == 0) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    p = ngx_pnalloc(c->pool, len);
    if (p == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_memcpy(p, text, len);

    cln->handler = ngx_http_realip_cleanup;
    ngx_http_set_ctx(r, ctx, ngx_http_realip_module);

    ctx->connection = c;
    ctx->sockaddr = c->sockaddr;
    ctx->socklen = c->socklen;
    ctx->addr_text = c->addr_text;

    c->sockaddr = addr->sockaddr;
    c->socklen = addr->socklen;
    c->addr_text.len = len;
    c->addr_text.data = p;

    return NGX_DECLINED;
}