#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int ssize_t ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_14__ {int rest; int frame_state; scalar_t__ stream_id; int flags; int setting_id; int setting_value; int send_window; void* state; TYPE_1__* connection; int /*<<< orphan*/  settings; int /*<<< orphan*/ * free; } ;
typedef  TYPE_4__ ngx_http_grpc_ctx_t ;
struct TYPE_15__ {int* last; int* pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {int init_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_V2_ACK_FLAG ; 
 int NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_grpc_send_settings_ack (TYPE_3__*,TYPE_4__*) ; 
 void* ngx_http_grpc_st_start ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_parse_settings(ngx_http_request_t *r, ngx_http_grpc_ctx_t *ctx,
    ngx_buf_t *b)
{
    u_char   ch, *p, *last;
    ssize_t  window_update;
    enum {
        sw_start = 0,
        sw_id,
        sw_id_2,
        sw_value,
        sw_value_2,
        sw_value_3,
        sw_value_4
    } state;

    if (b->last - b->pos < (ssize_t) ctx->rest) {
        last = b->last;

    } else {
        last = b->pos + ctx->rest;
    }

    state = ctx->frame_state;

    if (state == sw_start) {

        if (ctx->stream_id) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent settings frame "
                          "with non-zero stream id: %ui",
                          ctx->stream_id);
            return NGX_ERROR;
        }

        if (ctx->flags & NGX_HTTP_V2_ACK_FLAG) {
            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "grpc settings ack");

            if (ctx->rest != 0) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "upstream sent settings frame "
                              "with ack flag and non-zero length: %uz",
                              ctx->rest);
                return NGX_ERROR;
            }

            ctx->state = ngx_http_grpc_st_start;

            return NGX_OK;
        }

        if (ctx->rest % 6 != 0) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent settings frame "
                          "with invalid length: %uz",
                          ctx->rest);
            return NGX_ERROR;
        }

        if (ctx->free == NULL && ctx->settings++ > 1000) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent too many settings frames");
            return NGX_ERROR;
        }
    }

    for (p = b->pos; p < last; p++) {
        ch = *p;

#if 0
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "grpc settings byte: %02Xd s:%d", ch, state);
#endif

        switch (state) {

        case sw_start:
        case sw_id:
            ctx->setting_id = ch << 8;
            state = sw_id_2;
            break;

        case sw_id_2:
            ctx->setting_id |= ch;
            state = sw_value;
            break;

        case sw_value:
            ctx->setting_value = (ngx_uint_t) ch << 24;
            state = sw_value_2;
            break;

        case sw_value_2:
            ctx->setting_value |= ch << 16;
            state = sw_value_3;
            break;

        case sw_value_3:
            ctx->setting_value |= ch << 8;
            state = sw_value_4;
            break;

        case sw_value_4:
            ctx->setting_value |= ch;
            state = sw_id;

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "grpc setting: %ui %ui",
                           ctx->setting_id, ctx->setting_value);

            /*
             * The following settings are defined by the protocol:
             *
             * SETTINGS_HEADER_TABLE_SIZE, SETTINGS_ENABLE_PUSH,
             * SETTINGS_MAX_CONCURRENT_STREAMS, SETTINGS_INITIAL_WINDOW_SIZE,
             * SETTINGS_MAX_FRAME_SIZE, SETTINGS_MAX_HEADER_LIST_SIZE
             *
             * Only SETTINGS_INITIAL_WINDOW_SIZE seems to be needed in
             * a simple client.
             */

            if (ctx->setting_id == 0x04) {
                /* SETTINGS_INITIAL_WINDOW_SIZE */

                if (ctx->setting_value > NGX_HTTP_V2_MAX_WINDOW) {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "upstream sent settings frame "
                                  "with too large initial window size: %ui",
                                  ctx->setting_value);
                    return NGX_ERROR;
                }

                window_update = ctx->setting_value
                                - ctx->connection->init_window;
                ctx->connection->init_window = ctx->setting_value;

                if (ctx->send_window > 0
                    && window_update > (ssize_t) NGX_HTTP_V2_MAX_WINDOW
                                       - ctx->send_window)
                {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "upstream sent settings frame "
                                  "with too large initial window size: %ui",
                                  ctx->setting_value);
                    return NGX_ERROR;
                }

                ctx->send_window += window_update;
            }

            break;
        }
    }

    ctx->rest -= p - b->pos;
    ctx->frame_state = state;
    b->pos = p;

    if (ctx->rest > 0) {
        return NGX_AGAIN;
    }

    ctx->state = ngx_http_grpc_st_start;

    return ngx_http_grpc_send_settings_ack(r, ctx);
}