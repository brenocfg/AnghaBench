#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_7__ {TYPE_2__* free_bufs; } ;
typedef  TYPE_1__ ngx_http_charset_ctx_t ;
struct TYPE_8__ {TYPE_5__* buf; struct TYPE_8__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_9__ {scalar_t__ tag; int /*<<< orphan*/ * shadow; } ;

/* Variables and functions */
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_calloc_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_charset_get_buf(ngx_pool_t *pool, ngx_http_charset_ctx_t *ctx)
{
    ngx_chain_t  *cl;

    cl = ctx->free_bufs;

    if (cl) {
        ctx->free_bufs = cl->next;

        cl->buf->shadow = NULL;
        cl->next = NULL;

        return cl;
    }

    cl = ngx_alloc_chain_link(pool);
    if (cl == NULL) {
        return NULL;
    }

    cl->buf = ngx_calloc_buf(pool);
    if (cl->buf == NULL) {
        return NULL;
    }

    cl->next = NULL;

    cl->buf->tag = (ngx_buf_tag_t) &ngx_http_charset_filter_module;

    return cl;
}