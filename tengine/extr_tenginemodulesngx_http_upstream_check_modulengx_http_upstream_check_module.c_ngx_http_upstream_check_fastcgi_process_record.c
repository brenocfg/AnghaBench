#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int state; int length; size_t padding; } ;
typedef  TYPE_1__ ngx_http_upstream_check_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ ngx_http_status_t ;
typedef  int ngx_http_fastcgi_state_e ;
struct TYPE_10__ {int* pos; int* last; } ;
typedef  TYPE_3__ ngx_buf_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_HTTP_FASTCGI_END_REQUEST 140 
#define  NGX_HTTP_FASTCGI_STDERR 139 
#define  NGX_HTTP_FASTCGI_STDOUT 138 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_7__* ngx_cycle ; 
#define  ngx_http_fastcgi_st_content_length_hi 137 
#define  ngx_http_fastcgi_st_content_length_lo 136 
#define  ngx_http_fastcgi_st_data 135 
#define  ngx_http_fastcgi_st_padding 134 
#define  ngx_http_fastcgi_st_padding_length 133 
#define  ngx_http_fastcgi_st_request_id_hi 132 
#define  ngx_http_fastcgi_st_request_id_lo 131 
#define  ngx_http_fastcgi_st_reserved 130 
#define  ngx_http_fastcgi_st_type 129 
#define  ngx_http_fastcgi_st_version 128 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_fastcgi_process_record(
    ngx_http_upstream_check_ctx_t *ctx, ngx_buf_t *b, ngx_http_status_t *status)
{
    u_char                     ch, *p;
    ngx_http_fastcgi_state_e   state;

    state = ctx->state;

    for (p = b->pos; p < b->last; p++) {

        ch = *p;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "http fastcgi record byte: %02Xd", ch);

        switch (state) {

        case ngx_http_fastcgi_st_version:
            if (ch != 1) {
                ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                              "upstream sent unsupported FastCGI "
                              "protocol version: %d", ch);
                return NGX_ERROR;
            }
            state = ngx_http_fastcgi_st_type;
            break;

        case ngx_http_fastcgi_st_type:
            switch (ch) {
            case NGX_HTTP_FASTCGI_STDOUT:
            case NGX_HTTP_FASTCGI_STDERR:
            case NGX_HTTP_FASTCGI_END_REQUEST:
                status->code = (ngx_uint_t) ch;
                break;
            default:
                ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                              "upstream sent invalid FastCGI "
                              "record type: %d", ch);
                return NGX_ERROR;

            }
            state = ngx_http_fastcgi_st_request_id_hi;
            break;

        /* we support the single request per connection */

        case ngx_http_fastcgi_st_request_id_hi:
            if (ch != 0) {
                ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                              "upstream sent unexpected FastCGI "
                              "request id high byte: %d", ch);
                return NGX_ERROR;
            }
            state = ngx_http_fastcgi_st_request_id_lo;
            break;

        case ngx_http_fastcgi_st_request_id_lo:
            if (ch != 1) {
                ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                              "upstream sent unexpected FastCGI "
                              "request id low byte: %d", ch);
                return NGX_ERROR;
            }
            state = ngx_http_fastcgi_st_content_length_hi;
            break;

        case ngx_http_fastcgi_st_content_length_hi:
            ctx->length = ch << 8;
            state = ngx_http_fastcgi_st_content_length_lo;
            break;

        case ngx_http_fastcgi_st_content_length_lo:
            ctx->length |= (size_t) ch;
            state = ngx_http_fastcgi_st_padding_length;
            break;

        case ngx_http_fastcgi_st_padding_length:
            ctx->padding = (size_t) ch;
            state = ngx_http_fastcgi_st_reserved;
            break;

        case ngx_http_fastcgi_st_reserved:
            state = ngx_http_fastcgi_st_data;

            b->pos = p + 1;
            ctx->state = state;

            return NGX_OK;

        /* suppress warning */
        case ngx_http_fastcgi_st_data:
        case ngx_http_fastcgi_st_padding:
            break;
        }
    }

    ctx->state = state;

    return NGX_AGAIN;
}