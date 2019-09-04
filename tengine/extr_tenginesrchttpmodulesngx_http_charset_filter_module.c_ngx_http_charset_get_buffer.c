#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_8__ {TYPE_2__* free_buffers; } ;
typedef  TYPE_1__ ngx_http_charset_ctx_t ;
struct TYPE_9__ {TYPE_3__* buf; struct TYPE_9__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_10__ {int temporary; scalar_t__ tag; int /*<<< orphan*/ * shadow; scalar_t__ start; scalar_t__ pos; scalar_t__ end; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_create_temp_buf (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_charset_get_buffer(ngx_pool_t *pool, ngx_http_charset_ctx_t *ctx,
    size_t size)
{
    ngx_buf_t    *b;
    ngx_chain_t  *cl, **ll;

    for (ll = &ctx->free_buffers, cl = ctx->free_buffers;
         cl;
         ll = &cl->next, cl = cl->next)
    {
        b = cl->buf;

        if ((size_t) (b->end - b->start) >= size) {
            *ll = cl->next;
            cl->next = NULL;

            b->pos = b->start;
            b->temporary = 1;
            b->shadow = NULL;

            return cl;
        }
    }

    cl = ngx_alloc_chain_link(pool);
    if (cl == NULL) {
        return NULL;
    }

    cl->buf = ngx_create_temp_buf(pool, size);
    if (cl->buf == NULL) {
        return NULL;
    }

    cl->next = NULL;

    cl->buf->temporary = 1;
    cl->buf->tag = (ngx_buf_tag_t) &ngx_http_charset_filter_module;

    return cl;
}