#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ buffering; TYPE_5__* in; TYPE_2__* request; } ;
typedef  TYPE_3__ ngx_http_gzip_ctx_t ;
struct TYPE_16__ {size_t postpone_gzipping; } ;
typedef  TYPE_4__ ngx_http_gzip_conf_t ;
struct TYPE_17__ {struct TYPE_17__* next; TYPE_6__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_18__ {size_t last; size_t pos; scalar_t__ tag; scalar_t__ last_buf; scalar_t__ flush; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_13__ {int /*<<< orphan*/  buffered; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_GZIP_BUFFERED ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_5__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 size_t ngx_cpymem (size_t,size_t,size_t) ; 
 TYPE_6__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_gzip_filter_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_gzip_filter_buffer(ngx_http_gzip_ctx_t *ctx, ngx_chain_t *in)
{
    size_t                 size, buffered;
    ngx_buf_t             *b, *buf;
    ngx_chain_t           *cl, **ll;
    ngx_http_request_t    *r;
    ngx_http_gzip_conf_t  *conf;

    r = ctx->request;

    r->connection->buffered |= NGX_HTTP_GZIP_BUFFERED;

    buffered = 0;
    ll = &ctx->in;

    for (cl = ctx->in; cl; cl = cl->next) {
        buffered += cl->buf->last - cl->buf->pos;
        ll = &cl->next;
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_gzip_filter_module);

    while (in) {
        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NGX_ERROR;
        }

        b = in->buf;

        size = b->last - b->pos;
        buffered += size;

        if (b->flush || b->last_buf || buffered > conf->postpone_gzipping) {
            ctx->buffering = 0;
        }

        if (ctx->buffering && size) {

            buf = ngx_create_temp_buf(r->pool, size);
            if (buf == NULL) {
                return NGX_ERROR;
            }

            buf->last = ngx_cpymem(buf->pos, b->pos, size);
            b->pos = b->last;

            buf->last_buf = b->last_buf;
            buf->tag = (ngx_buf_tag_t) &ngx_http_gzip_filter_module;

            cl->buf = buf;

        } else {
            cl->buf = b;
        }

        *ll = cl;
        ll = &cl->next;
        in = in->next;
    }

    *ll = NULL;

    return ctx->buffering ? NGX_OK : NGX_DONE;
}