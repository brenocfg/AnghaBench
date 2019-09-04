#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {scalar_t__ send_window; TYPE_4__* request; scalar_t__ exhausted; } ;
typedef  TYPE_5__ ngx_http_v2_stream_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  id; TYPE_5__* stream; struct TYPE_18__* index; } ;
typedef  TYPE_6__ ngx_http_v2_node_t ;
struct TYPE_19__ {TYPE_2__* connection; TYPE_6__** streams_index; TYPE_1__* http_connection; } ;
typedef  TYPE_7__ ngx_http_v2_connection_t ;
struct TYPE_20__ {int ready; int /*<<< orphan*/  (* handler ) (TYPE_8__*) ;int /*<<< orphan*/  delayed; scalar_t__ active; } ;
typedef  TYPE_8__ ngx_event_t ;
struct TYPE_16__ {TYPE_3__* connection; } ;
struct TYPE_15__ {TYPE_8__* write; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_FLOW_CTRL_ERROR ; 
 scalar_t__ NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_get_module_srv_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_http_v2_index_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 scalar_t__ ngx_http_v2_terminate_stream (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_adjust_windows(ngx_http_v2_connection_t *h2c, ssize_t delta)
{
    ngx_uint_t               i, size;
    ngx_event_t             *wev;
    ngx_http_v2_node_t      *node;
    ngx_http_v2_stream_t    *stream;
    ngx_http_v2_srv_conf_t  *h2scf;

    h2scf = ngx_http_get_module_srv_conf(h2c->http_connection->conf_ctx,
                                         ngx_http_v2_module);

    size = ngx_http_v2_index_size(h2scf);

    for (i = 0; i < size; i++) {

        for (node = h2c->streams_index[i]; node; node = node->index) {
            stream = node->stream;

            if (stream == NULL) {
                continue;
            }

            if (delta > 0
                && stream->send_window
                      > (ssize_t) (NGX_HTTP_V2_MAX_WINDOW - delta))
            {
                if (ngx_http_v2_terminate_stream(h2c, stream,
                                                 NGX_HTTP_V2_FLOW_CTRL_ERROR)
                    == NGX_ERROR)
                {
                    return NGX_ERROR;
                }

                continue;
            }

            stream->send_window += delta;

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                           "http2:%ui adjusted window: %z",
                           node->id, stream->send_window);

            if (stream->send_window > 0 && stream->exhausted) {
                stream->exhausted = 0;

                wev = stream->request->connection->write;

                wev->active = 0;
                wev->ready = 1;

                if (!wev->delayed) {
                    wev->handler(wev);
                }
            }
        }
    }

    return NGX_OK;
}