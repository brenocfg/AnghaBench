#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {int content_length_n; } ;
struct TYPE_18__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  request_body_no_buffering; TYPE_2__ headers_in; TYPE_1__* connection; int /*<<< orphan*/  request_length; TYPE_4__* request_body; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_19__ {int received; int /*<<< orphan*/  busy; int /*<<< orphan*/  free; scalar_t__ rest; TYPE_7__* buf; } ;
typedef  TYPE_4__ ngx_http_request_body_t ;
struct TYPE_20__ {int client_max_body_size; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
struct TYPE_21__ {TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_22__ {scalar_t__ pos; scalar_t__ last; int temporary; scalar_t__ start; scalar_t__ end; int last_buf; int /*<<< orphan*/  flush; scalar_t__ tag; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_BAD_REQUEST ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_ENTITY_TOO_LARGE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__**,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_top_request_body_filter (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_filter_request_body(ngx_http_request_t *r)
{
    ngx_buf_t                 *b, *buf;
    ngx_int_t                  rc;
    ngx_chain_t               *cl;
    ngx_http_request_body_t   *rb;
    ngx_http_core_loc_conf_t  *clcf;

    rb = r->request_body;
    buf = rb->buf;

    if (buf->pos == buf->last && rb->rest) {
        cl = NULL;
        goto update;
    }

    cl = ngx_chain_get_free_buf(r->pool, &rb->free);
    if (cl == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    b = cl->buf;

    ngx_memzero(b, sizeof(ngx_buf_t));

    if (buf->pos != buf->last) {
        r->request_length += buf->last - buf->pos;
        rb->received += buf->last - buf->pos;

        if (r->headers_in.content_length_n != -1) {
            if (rb->received > r->headers_in.content_length_n) {
                ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                              "client intended to send body data "
                              "larger than declared");

                return NGX_HTTP_BAD_REQUEST;
            }

        } else {
            clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

            if (clcf->client_max_body_size
                && rb->received > clcf->client_max_body_size)
            {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "client intended to send too large chunked body: "
                              "%O bytes", rb->received);

                return NGX_HTTP_REQUEST_ENTITY_TOO_LARGE;
            }
        }

        b->temporary = 1;
        b->pos = buf->pos;
        b->last = buf->last;
        b->start = b->pos;
        b->end = b->last;

        buf->pos = buf->last;
    }

    if (!rb->rest) {
        if (r->headers_in.content_length_n != -1
            && r->headers_in.content_length_n != rb->received)
        {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client prematurely closed stream: "
                          "only %O out of %O bytes of request body received",
                          rb->received, r->headers_in.content_length_n);

            return NGX_HTTP_BAD_REQUEST;
        }

        b->last_buf = 1;
    }

    b->tag = (ngx_buf_tag_t) &ngx_http_v2_filter_request_body;
    b->flush = r->request_body_no_buffering;

update:

    rc = ngx_http_top_request_body_filter(r, cl);

    ngx_chain_update_chains(r->pool, &rb->free, &rb->busy, &cl,
                            (ngx_buf_tag_t) &ngx_http_v2_filter_request_body);

    return rc;
}