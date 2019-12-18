#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {TYPE_2__ output; int /*<<< orphan*/  free_bufs; TYPE_5__* out_bufs; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_12__ {TYPE_1__* buf; struct TYPE_12__* next; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_8__ {int flush; int memory; int /*<<< orphan*/  tag; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_5__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_copy_body_buffer(ngx_http_tfs_t *t, ssize_t bytes, u_char *body)
{
    ngx_http_request_t  *r = t->data;

    ngx_chain_t  *cl, **ll;

    for (cl = t->out_bufs, ll = &t->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    cl = ngx_chain_get_free_buf(r->pool, &t->free_bufs);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    *ll = cl;

    cl->buf->flush = 1;
    cl->buf->memory = 1;

    cl->buf->pos = body;
    cl->buf->last = body + bytes;
    cl->buf->tag = t->output.tag;

    return NGX_OK;
}