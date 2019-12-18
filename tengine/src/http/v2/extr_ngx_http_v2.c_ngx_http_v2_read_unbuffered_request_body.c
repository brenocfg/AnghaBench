#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {size_t recv_window; int skip_data; TYPE_3__* node; TYPE_5__* connection; } ;
typedef  TYPE_4__ ngx_http_v2_stream_t ;
struct TYPE_19__ {scalar_t__ length; TYPE_4__* stream; } ;
struct TYPE_22__ {TYPE_2__ state; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_23__ {TYPE_8__* connection; TYPE_1__* request_body; TYPE_4__* stream; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_24__ {int /*<<< orphan*/  client_body_timeout; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_25__ {int timedout; TYPE_16__* read; int /*<<< orphan*/  log; scalar_t__ error; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_26__ {size_t pos; size_t start; size_t last; size_t end; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_20__ {int /*<<< orphan*/  id; } ;
struct TYPE_18__ {TYPE_9__* buf; int /*<<< orphan*/ * busy; int /*<<< orphan*/  rest; } ;
struct TYPE_17__ {scalar_t__ timedout; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_BAD_REQUEST ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_v2_filter_request_body (TYPE_6__*) ; 
 scalar_t__ ngx_http_v2_send_output_queue (TYPE_5__*) ; 
 scalar_t__ ngx_http_v2_send_window_update (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_v2_read_unbuffered_request_body(ngx_http_request_t *r)
{
    size_t                     window;
    ngx_buf_t                 *buf;
    ngx_int_t                  rc;
    ngx_connection_t          *fc;
    ngx_http_v2_stream_t      *stream;
    ngx_http_v2_connection_t  *h2c;
    ngx_http_core_loc_conf_t  *clcf;

    stream = r->stream;
    fc = r->connection;

    if (fc->read->timedout) {
        if (stream->recv_window) {
            stream->skip_data = 1;
            fc->timedout = 1;

            return NGX_HTTP_REQUEST_TIME_OUT;
        }

        fc->read->timedout = 0;
    }

    if (fc->error) {
        stream->skip_data = 1;
        return NGX_HTTP_BAD_REQUEST;
    }

    rc = ngx_http_v2_filter_request_body(r);

    if (rc != NGX_OK) {
        stream->skip_data = 1;
        return rc;
    }

    if (!r->request_body->rest) {
        return NGX_OK;
    }

    if (r->request_body->busy != NULL) {
        return NGX_AGAIN;
    }

    buf = r->request_body->buf;

    buf->pos = buf->start;
    buf->last = buf->start;

    window = buf->end - buf->start;
    h2c = stream->connection;

    if (h2c->state.stream == stream) {
        window -= h2c->state.length;
    }

    if (window <= stream->recv_window) {
        if (window < stream->recv_window) {
            ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                          "http2 negative window update");
            stream->skip_data = 1;
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        return NGX_AGAIN;
    }

    if (ngx_http_v2_send_window_update(h2c, stream->node->id,
                                       window - stream->recv_window)
        == NGX_ERROR)
    {
        stream->skip_data = 1;
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (ngx_http_v2_send_output_queue(h2c) == NGX_ERROR) {
        stream->skip_data = 1;
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (stream->recv_window == 0) {
        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
        ngx_add_timer(fc->read, clcf->client_body_timeout);
    }

    stream->recv_window = window;

    return NGX_AGAIN;
}