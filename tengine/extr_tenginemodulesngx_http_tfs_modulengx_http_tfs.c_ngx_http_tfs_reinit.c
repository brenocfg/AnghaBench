#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {int /*<<< orphan*/ * busy; int /*<<< orphan*/ * in; TYPE_2__* buf; TYPE_11__* free; } ;
struct TYPE_17__ {int header_size; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  parse_state; TYPE_4__ header_buffer; TYPE_3__ output; TYPE_7__* request_bufs; scalar_t__ request_sent; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; struct TYPE_18__* main; TYPE_1__* request_body; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_19__ {struct TYPE_19__* next; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_14__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_13__ {scalar_t__ temp_file; } ;
struct TYPE_12__ {int /*<<< orphan*/ * next; TYPE_2__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_HEADER ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_11__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_send_handler ; 

ngx_int_t
ngx_http_tfs_reinit(ngx_http_request_t *r, ngx_http_tfs_t *t)
{
    ngx_chain_t  *cl, *cl_next;

    t->request_sent = 0;

    for (cl = t->request_bufs; cl; cl = cl_next) {
        cl_next = cl->next;
        ngx_free_chain(r->pool, cl);
    }

    /* reinit the subrequest's ngx_output_chain() context */
    if (r->request_body && r->request_body->temp_file
        && r != r->main && t->output.buf)
    {
        t->output.free = ngx_alloc_chain_link(r->pool);
        if (t->output.free == NULL) {
            return NGX_ERROR;
        }

        t->output.free->buf = t->output.buf;
        t->output.free->next = NULL;

        t->output.buf->pos = t->output.buf->start;
        t->output.buf->last = t->output.buf->start;
    }

    t->output.buf = NULL;
    t->output.in = NULL;
    t->output.busy = NULL;

    t->header_buffer.pos = t->header_buffer.start;
    t->header_buffer.last = t->header_buffer.start;

    t->parse_state = NGX_HTTP_TFS_HEADER;
    t->header_size = sizeof(ngx_http_tfs_header_t);
    t->write_event_handler = ngx_http_tfs_send_handler;

    return NGX_OK;
}