#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_25__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
struct TYPE_38__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_9__ ngx_pool_cleanup_t ;
struct TYPE_36__ {int /*<<< orphan*/  trailers; int /*<<< orphan*/  headers; } ;
struct TYPE_35__ {int allocated; int /*<<< orphan*/  tag; TYPE_25__* free; int /*<<< orphan*/  sendfile; } ;
struct TYPE_34__ {int temporary; int /*<<< orphan*/  tag; int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
struct TYPE_29__ {scalar_t__ limit; TYPE_12__* connection; int /*<<< orphan*/ * out; int /*<<< orphan*/ ** last; int /*<<< orphan*/  pool; } ;
struct TYPE_26__ {int /*<<< orphan*/ * send_pool; TYPE_7__ headers_in; TYPE_6__ output; TYPE_5__ buffer; TYPE_4__* conf; scalar_t__ request_sent; TYPE_1__ writer; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  write_event_handler; } ;
typedef  TYPE_10__ ngx_http_upstream_t ;
struct TYPE_27__ {int /*<<< orphan*/  pool; TYPE_8__* connection; TYPE_3__* request_body; struct TYPE_27__* main; TYPE_10__* upstream; } ;
typedef  TYPE_11__ ngx_http_request_t ;
struct TYPE_28__ {int /*<<< orphan*/  sendfile; TYPE_11__* data; } ;
typedef  TYPE_12__ ngx_connection_t ;
struct TYPE_37__ {int /*<<< orphan*/  log; } ;
struct TYPE_33__ {int buffer_size; } ;
struct TYPE_32__ {TYPE_2__* buf; scalar_t__ temp_file; } ;
struct TYPE_31__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_30__ {int /*<<< orphan*/ * next; TYPE_2__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DEFAULT_POOL_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_25__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_finalize_request (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_send_pool_cleanup ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_header ; 
 scalar_t__ ngx_http_upstream_reinit (TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request (TYPE_11__*,TYPE_10__*,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request_handler ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_12__*,TYPE_11__*) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ngx_http_multi_upstream_init_request(ngx_connection_t *pc, ngx_http_request_t *r)
{
    ngx_http_upstream_t         *u;
    ngx_http_request_t          *fake_r;
    ngx_pool_cleanup_t          *cln;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "multi: http upstream init request: %p, %p", pc, r);

    u = r->upstream;
    fake_r = pc->data;

    u->write_event_handler = ngx_http_upstream_send_request_handler;
    u->read_event_handler = ngx_http_upstream_process_header;

    u->output.sendfile = pc->sendfile;

    /* init or reinit the ngx_output_chain() and ngx_chain_writer() contexts */
    u->writer.pool = fake_r->pool;
    u->writer.out = NULL;
    u->writer.last = &u->writer.out;
    u->writer.connection = pc;
    u->writer.limit = 0;

    if (u->request_sent) {
        if (ngx_http_upstream_reinit(r, u) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }
    }

    if (r->request_body
        && r->request_body->buf
        && r->request_body->temp_file
        && r == r->main)
    {
        /*
         * the r->request_body->buf can be reused for one request only,
         * the subrequests should allocate their own temporary bufs
         */

        u->output.free = ngx_alloc_chain_link(r->pool);
        if (u->output.free == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        u->output.free->buf = r->request_body->buf;
        u->output.free->next = NULL;
        u->output.allocated = 1;

        r->request_body->buf->pos = r->request_body->buf->start;
        r->request_body->buf->last = r->request_body->buf->start;
        r->request_body->buf->tag = u->output.tag;
    }

    u->request_sent = 0;

    if (u->buffer.start == NULL) {
        u->buffer.start = ngx_palloc(r->pool, u->conf->buffer_size);
        if (u->buffer.start == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        u->buffer.pos = u->buffer.start;
        u->buffer.last = u->buffer.start;
        u->buffer.end = u->buffer.start + u->conf->buffer_size;
        u->buffer.temporary = 1;

        u->buffer.tag = u->output.tag;

        if (ngx_list_init(&u->headers_in.headers, r->pool, 8,
                          sizeof(ngx_table_elt_t))
            != NGX_OK)
        {
            ngx_http_multi_upstream_finalize_request(pc,
                                                     NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        if (ngx_list_init(&u->headers_in.trailers, r->pool, 2,
                          sizeof(ngx_table_elt_t))
            != NGX_OK)
        {
            ngx_http_multi_upstream_finalize_request(pc,
                                                     NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }
    }

    if (u->send_pool == NULL) {
        u->send_pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, r->connection->log);
        if (u->send_pool == NULL) {
            return;
        }

        cln = ngx_pool_cleanup_add(r->pool, 0);
        if (cln == NULL) {
            return;
        }

        cln->handler = ngx_http_multi_upstream_send_pool_cleanup;
        cln->data = u->send_pool;

    }

    ngx_http_upstream_send_request(r, u, 1);
}