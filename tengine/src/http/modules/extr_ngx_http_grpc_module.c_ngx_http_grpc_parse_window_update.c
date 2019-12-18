#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {int rest; int frame_state; int window_update; size_t send_window; TYPE_2__* connection; scalar_t__ stream_id; int /*<<< orphan*/  state; } ;
typedef  TYPE_4__ ngx_http_grpc_ctx_t ;
struct TYPE_13__ {int* last; int* pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_10__ {scalar_t__ send_window; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_grpc_st_start ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_parse_window_update(ngx_http_request_t *r,
    ngx_http_grpc_ctx_t *ctx, ngx_buf_t *b)
{
    u_char  ch, *p, *last;
    enum {
        sw_start = 0,
        sw_size_2,
        sw_size_3,
        sw_size_4
    } state;

    if (b->last - b->pos < (ssize_t) ctx->rest) {
        last = b->last;

    } else {
        last = b->pos + ctx->rest;
    }

    state = ctx->frame_state;

    if (state == sw_start) {
        if (ctx->rest != 4) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent window update frame "
                          "with invalid length: %uz",
                          ctx->rest);
            return NGX_ERROR;
        }
    }

    for (p = b->pos; p < last; p++) {
        ch = *p;

#if 0
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "grpc window update byte: %02Xd s:%d", ch, state);
#endif

        switch (state) {

        case sw_start:
            ctx->window_update = (ch & 0x7f) << 24;
            state = sw_size_2;
            break;

        case sw_size_2:
            ctx->window_update |= ch << 16;
            state = sw_size_3;
            break;

        case sw_size_3:
            ctx->window_update |= ch << 8;
            state = sw_size_4;
            break;

        case sw_size_4:
            ctx->window_update |= ch;
            state = sw_start;
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

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "grpc window update: %ui", ctx->window_update);

    if (ctx->stream_id) {

        if (ctx->window_update > (size_t) NGX_HTTP_V2_MAX_WINDOW
                                 - ctx->send_window)
        {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent too large window update");
            return NGX_ERROR;
        }

        ctx->send_window += ctx->window_update;

    } else {

        if (ctx->window_update > NGX_HTTP_V2_MAX_WINDOW
                                 - ctx->connection->send_window)
        {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent too large window update");
            return NGX_ERROR;
        }

        ctx->connection->send_window += ctx->window_update;
    }

    return NGX_OK;
}