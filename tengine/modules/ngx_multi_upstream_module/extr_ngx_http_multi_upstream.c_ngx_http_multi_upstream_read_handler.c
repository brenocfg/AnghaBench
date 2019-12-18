#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
struct TYPE_43__ {TYPE_8__* cur; } ;
typedef  TYPE_6__ ngx_multi_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_40__ {scalar_t__ status_n; int /*<<< orphan*/  trailers; int /*<<< orphan*/  headers; } ;
struct TYPE_42__ {scalar_t__ cached; } ;
struct TYPE_36__ {scalar_t__ pos; scalar_t__ start; scalar_t__ last; scalar_t__ end; int temporary; int /*<<< orphan*/  tag; } ;
struct TYPE_39__ {int /*<<< orphan*/  tag; } ;
struct TYPE_44__ {scalar_t__ (* process_header ) (TYPE_8__*) ;int /*<<< orphan*/  header_sent; TYPE_3__ headers_in; TYPE_1__* state; TYPE_5__ peer; scalar_t__ valid_header_in; TYPE_4__* conf; TYPE_10__ buffer; TYPE_2__ output; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
struct TYPE_45__ {TYPE_9__* connection; TYPE_7__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_46__ {scalar_t__ (* recv ) (TYPE_9__*,scalar_t__,scalar_t__) ;TYPE_13__* log; int /*<<< orphan*/  read; TYPE_8__* data; } ;
typedef  TYPE_9__ ngx_connection_t ;
typedef  TYPE_10__ ngx_buf_t ;
struct TYPE_41__ {int buffer_size; int /*<<< orphan*/  read_timeout; } ;
struct TYPE_38__ {void* response_time; void* header_time; } ;
struct TYPE_37__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_BAD_GATEWAY ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_INVALID_HEADER ; 
 scalar_t__ NGX_HTTP_UPSTREAM_GET_BODY_DATA ; 
 scalar_t__ NGX_HTTP_UPSTREAM_HEADER_END ; 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 scalar_t__ NGX_HTTP_UPSTREAM_PARSE_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ngx_current_msec ; 
 TYPE_6__* ngx_get_multi_connection (TYPE_9__*) ; 
 scalar_t__ ngx_handle_read_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_finalize_request (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_next (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_process_non_buffered_request (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_send_response (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_8__*,TYPE_7__*,scalar_t__) ; 
 scalar_t__ ngx_http_upstream_intercept_errors (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_upstream_process_headers (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_upstream_test_connect (TYPE_9__*) ; 
 scalar_t__ ngx_http_upstream_test_next (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_9__*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_8__*) ; 

void
ngx_http_multi_upstream_read_handler(ngx_connection_t *pc)
{
    ssize_t                  n;
    ngx_int_t                rc;
    ngx_http_request_t      *r, *fake_r, *real_r;
    ngx_http_upstream_t     *u, *fake_u, *real_u;
    ngx_connection_t        *c, *real_c;
    ngx_multi_connection_t  *multi_c;
    ngx_buf_t               *b;

    c = pc;
    multi_c = ngx_get_multi_connection(pc);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                   "multi: http upstream read handler %p", pc);

    pc->log->action = "reading from multi upstream";

    if (ngx_http_upstream_test_connect(pc) != NGX_OK) {
        ngx_http_multi_upstream_next(pc, NGX_HTTP_UPSTREAM_FT_ERROR);
        return;
    }

    r = pc->data;           //fake_r
    u = r->upstream;        //fake_u
    fake_u = r->upstream;

    fake_r = r;

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

    //fake_u buffer
    b = &fake_u->buffer;

    for ( ;; ) {
        if (b->last == b->end) {
            ngx_log_debug4(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                           "multi: read buffer full %p, %p, %p, %p"
                           , b->start, b->end, b->pos, b->last);
        } else {
            n = c->recv(c, b->last, b->end - b->last);

            if (n == NGX_AGAIN) {
                ngx_add_timer(pc->read, u->conf->read_timeout);

                if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
                    ngx_http_multi_upstream_finalize_request(pc,
                            NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return;
                }

                return;
            }

            if (n == 0) {
                ngx_log_error(NGX_LOG_ERR, c->log, 0,
                        "upstream prematurely closed connection");
            }

            if (n == NGX_ERROR || n == 0) {
                ngx_http_multi_upstream_next(pc, NGX_HTTP_UPSTREAM_FT_ERROR);
                return;
            }

            b->last += n;
        }

#if 0
        u->valid_header_in = 0;

        u->peer.cached = 0;
#endif

        for ( ; ; ) {
            ngx_log_debug5(NGX_LOG_DEBUG_HTTP, c->log, 0
                    , "multi: process parse start: %d, %p, %p, %p, %p"
                    , b->last - b->pos, b->start, b->end, b->pos, b->last);
            rc = u->process_header(fake_r);

            ngx_log_debug5(NGX_LOG_DEBUG_HTTP, c->log, 0
                    , "multi: process parse end: %d, %p, %p, %p, %p"
                    , b->last - b->pos, b->start, b->end, b->pos, b->last);

            if (rc == NGX_AGAIN) {
                if (b->last == b->end && b->pos == b->last) {
                    b->pos = b->start;
                    b->last = b->start;
                }

                break;
            }

            if (rc == NGX_HTTP_UPSTREAM_INVALID_HEADER) {
                ngx_http_multi_upstream_next(pc, NGX_HTTP_UPSTREAM_FT_INVALID_HEADER);
                return;
            }

            if (rc == NGX_ERROR) {
                ngx_http_multi_upstream_finalize_request(pc, NGX_HTTP_INTERNAL_SERVER_ERROR);
                return;
            }

            /* rc == NGX_OK || rc == NGX_ERROR */

            if (!multi_c->cur) {
                ngx_log_error(NGX_LOG_ERR, c->log, 0,
                              "multi: upstream next because parse cur is empty");
                ngx_http_multi_upstream_finalize_request(pc, NGX_HTTP_INTERNAL_SERVER_ERROR);
                return;
            }

            real_r = multi_c->cur;
            real_u = real_r->upstream;
            real_c = real_r->connection;

            if (rc == NGX_HTTP_UPSTREAM_HEADER_END) {
                real_u->state->header_time = ngx_current_msec - real_u->state->response_time;

                if (real_u->headers_in.status_n >= NGX_HTTP_SPECIAL_RESPONSE) {

                    if (ngx_http_upstream_test_next(real_r, real_u) == NGX_OK) {
                        continue;
                    }

                    if (ngx_http_upstream_intercept_errors(real_r, real_u) == NGX_OK) {
                        continue;
                    }
                }

                if (ngx_http_upstream_process_headers(real_r, real_u) != NGX_OK) {
                    continue;
                }

                ngx_http_multi_upstream_send_response(real_r, real_u);
            } else if (rc == NGX_HTTP_UPSTREAM_GET_BODY_DATA) {
                if (!real_u->header_sent) {
                    ngx_log_error(NGX_LOG_INFO, c->log, 0,
                                  "multi: get body immediate %p", fake_r);
                    //handle header first
                    real_u->state->header_time = ngx_current_msec - real_u->state->response_time;
                    if (real_u->headers_in.status_n >= NGX_HTTP_SPECIAL_RESPONSE) {
                        if (ngx_http_upstream_test_next(real_r, real_u) == NGX_OK) {
                            continue;
                        }

                        if (ngx_http_upstream_intercept_errors(real_r, real_u) == NGX_OK) {
                            continue;
                        }
                    }

                    if (ngx_http_upstream_process_headers(real_r, real_u) != NGX_OK) {
                        continue;
                    }

                    ngx_http_multi_upstream_send_response(real_r, real_u);
                }

                ngx_http_multi_upstream_process_non_buffered_request(real_r);
            } else if (rc == NGX_HTTP_UPSTREAM_PARSE_ERROR) {
                ngx_log_error(NGX_LOG_WARN, c->log, 0,
                              "multi: parse get error %p", fake_r);
                if (!real_u->header_sent) {
                    ngx_http_upstream_finalize_request(real_r, real_u, NGX_HTTP_BAD_GATEWAY);
                } else {
                    ngx_http_upstream_finalize_request(real_r, real_u, NGX_ERROR);
                }
            } else {
                ngx_log_error(NGX_LOG_ERR, c->log, 0,
                              "multi: parse code unknown: %d", rc);
                if (!real_u->header_sent) {
                    ngx_http_upstream_finalize_request(real_r, real_u, NGX_HTTP_INTERNAL_SERVER_ERROR);
                } else {
                    ngx_http_upstream_finalize_request(real_r, real_u, NGX_ERROR);
                }
            }

            ngx_http_run_posted_requests(real_c);
        }
    }
}