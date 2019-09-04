#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_10__ {int gzheader; TYPE_3__* out; } ;
typedef  TYPE_2__ ngx_http_gzip_ctx_t ;
struct TYPE_11__ {struct TYPE_11__* next; TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_12__ {int memory; int* pos; int* last; } ;
typedef  TYPE_4__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
#define  Z_DEFLATED 128 
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_gzip_filter_gzheader(ngx_http_request_t *r, ngx_http_gzip_ctx_t *ctx)
{
    ngx_buf_t      *b;
    ngx_chain_t    *cl;
    static u_char  gzheader[10] =
                               { 0x1f, 0x8b, Z_DEFLATED, 0, 0, 0, 0, 0, 0, 3 };

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_ERROR;
    }

    b->memory = 1;
    b->pos = gzheader;
    b->last = b->pos + 10;

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf = b;
    cl->next = ctx->out;
    ctx->out = cl;

    ctx->gzheader = 1;

    return NGX_OK;
}