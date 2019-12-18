#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
typedef  int ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_13__ {int frame_state; scalar_t__ type; int parsing_headers; int flags; size_t rest; int end_stream; size_t padding; scalar_t__ fragment_state; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ ngx_http_grpc_ctx_t ;
struct TYPE_14__ {size_t* last; size_t* pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_PARSE_HEADER_DONE ; 
 scalar_t__ NGX_HTTP_V2_CONTINUATION_FRAME ; 
 int NGX_HTTP_V2_END_HEADERS_FLAG ; 
 int NGX_HTTP_V2_END_STREAM_FLAG ; 
 scalar_t__ NGX_HTTP_V2_HEADERS_FRAME ; 
 int NGX_HTTP_V2_PADDED_FLAG ; 
 int NGX_HTTP_V2_PRIORITY_FLAG ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_grpc_parse_fragment (TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_grpc_st_start ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_parse_header(ngx_http_request_t *r, ngx_http_grpc_ctx_t *ctx,
    ngx_buf_t *b)
{
    u_char     ch, *p, *last;
    size_t     min;
    ngx_int_t  rc;
    enum {
        sw_start = 0,
        sw_padding_length,
        sw_dependency,
        sw_dependency_2,
        sw_dependency_3,
        sw_dependency_4,
        sw_weight,
        sw_fragment,
        sw_padding
    } state;

    state = ctx->frame_state;

    if (state == sw_start) {

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "grpc parse header: start");

        if (ctx->type == NGX_HTTP_V2_HEADERS_FRAME) {
            ctx->parsing_headers = 1;
            ctx->fragment_state = 0;

            min = (ctx->flags & NGX_HTTP_V2_PADDED_FLAG ? 1 : 0)
                  + (ctx->flags & NGX_HTTP_V2_PRIORITY_FLAG ? 5 : 0);

            if (ctx->rest < min) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "upstream sent headers frame "
                              "with invalid length: %uz",
                              ctx->rest);
                return NGX_ERROR;
            }

            if (ctx->flags & NGX_HTTP_V2_END_STREAM_FLAG) {
                ctx->end_stream = 1;
            }

            if (ctx->flags & NGX_HTTP_V2_PADDED_FLAG) {
                state = sw_padding_length;

            } else if (ctx->flags & NGX_HTTP_V2_PRIORITY_FLAG) {
                state = sw_dependency;

            } else {
                state = sw_fragment;
            }

        } else if (ctx->type == NGX_HTTP_V2_CONTINUATION_FRAME) {
            state = sw_fragment;
        }

        ctx->padding = 0;
        ctx->frame_state = state;
    }

    if (state < sw_fragment) {

        if (b->last - b->pos < (ssize_t) ctx->rest) {
            last = b->last;

        } else {
            last = b->pos + ctx->rest;
        }

        for (p = b->pos; p < last; p++) {
            ch = *p;

#if 0
            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "grpc header byte: %02Xd s:%d", ch, state);
#endif

            /*
             * headers frame:
             *
             * +---------------+
             * |Pad Length? (8)|
             * +-+-------------+----------------------------------------------+
             * |E|                 Stream Dependency? (31)                    |
             * +-+-------------+----------------------------------------------+
             * |  Weight? (8)  |
             * +-+-------------+----------------------------------------------+
             * |                   Header Block Fragment (*)                ...
             * +--------------------------------------------------------------+
             * |                           Padding (*)                      ...
             * +--------------------------------------------------------------+
             */

            switch (state) {

            case sw_padding_length:

                ctx->padding = ch;

                if (ctx->flags & NGX_HTTP_V2_PRIORITY_FLAG) {
                    state = sw_dependency;
                    break;
                }

                goto fragment;

            case sw_dependency:
                state = sw_dependency_2;
                break;

            case sw_dependency_2:
                state = sw_dependency_3;
                break;

            case sw_dependency_3:
                state = sw_dependency_4;
                break;

            case sw_dependency_4:
                state = sw_weight;
                break;

            case sw_weight:
                goto fragment;

            /* suppress warning */
            case sw_start:
            case sw_fragment:
            case sw_padding:
                break;
            }
        }

        ctx->rest -= p - b->pos;
        b->pos = p;

        ctx->frame_state = state;
        return NGX_AGAIN;

    fragment:

        p++;
        ctx->rest -= p - b->pos;
        b->pos = p;

        if (ctx->padding > ctx->rest) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent http2 frame with too long "
                          "padding: %d in frame %uz",
                          ctx->padding, ctx->rest);
            return NGX_ERROR;
        }

        state = sw_fragment;
        ctx->frame_state = state;
    }

    if (state == sw_fragment) {

        rc = ngx_http_grpc_parse_fragment(r, ctx, b);

        if (rc == NGX_AGAIN) {
            return NGX_AGAIN;
        }

        if (rc == NGX_ERROR) {
            return NGX_ERROR;
        }

        if (rc == NGX_OK) {
            return NGX_OK;
        }

        /* rc == NGX_DONE */

        state = sw_padding;
        ctx->frame_state = state;
    }

    if (state == sw_padding) {

        if (b->last - b->pos < (ssize_t) ctx->rest) {

            ctx->rest -= b->last - b->pos;
            b->pos = b->last;

            return NGX_AGAIN;
        }

        b->pos += ctx->rest;
        ctx->rest = 0;

        ctx->state = ngx_http_grpc_st_start;

        if (ctx->flags & NGX_HTTP_V2_END_HEADERS_FLAG) {

            if (ctx->fragment_state) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "upstream sent truncated http2 header");
                return NGX_ERROR;
            }

            ctx->parsing_headers = 0;

            return NGX_HTTP_PARSE_HEADER_DONE;
        }

        return NGX_AGAIN;
    }

    /* unreachable */

    return NGX_ERROR;
}