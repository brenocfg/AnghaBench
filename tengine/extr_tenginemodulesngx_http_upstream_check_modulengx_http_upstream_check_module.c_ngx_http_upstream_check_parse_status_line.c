#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int state; } ;
typedef  TYPE_1__ ngx_http_upstream_check_ctx_t ;
struct TYPE_8__ {int code; int count; char* start; char* end; } ;
typedef  TYPE_2__ ngx_http_status_t ;
struct TYPE_9__ {char* pos; char* last; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
#define  CR 129 
#define  LF 128 
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_parse_status_line(ngx_http_upstream_check_ctx_t *ctx,
    ngx_buf_t *b, ngx_http_status_t *status)
{
    u_char ch, *p;
    enum {
        sw_start = 0,
        sw_H,
        sw_HT,
        sw_HTT,
        sw_HTTP,
        sw_first_major_digit,
        sw_major_digit,
        sw_first_minor_digit,
        sw_minor_digit,
        sw_status,
        sw_space_after_status,
        sw_status_text,
        sw_almost_done
    } state;

    state = ctx->state;

    for (p = b->pos; p < b->last; p++) {
        ch = *p;

        switch (state) {

        /* "HTTP/" */
        case sw_start:
            if (ch != 'H') {
                return NGX_ERROR;
            }

            state = sw_H;
            break;

        case sw_H:
            if (ch != 'T') {
                return NGX_ERROR;
            }

            state = sw_HT;
            break;

        case sw_HT:
            if (ch != 'T') {
                return NGX_ERROR;
            }

            state = sw_HTT;
            break;

        case sw_HTT:
            if (ch != 'P') {
                return NGX_ERROR;
            }

            state = sw_HTTP;
            break;

        case sw_HTTP:
            if (ch != '/') {
                return NGX_ERROR;
            }

            state = sw_first_major_digit;
            break;

        /* the first digit of major HTTP version */
        case sw_first_major_digit:
            if (ch < '1' || ch > '9') {
                return NGX_ERROR;
            }

            state = sw_major_digit;
            break;

        /* the major HTTP version or dot */
        case sw_major_digit:
            if (ch == '.') {
                state = sw_first_minor_digit;
                break;
            }

            if (ch < '0' || ch > '9') {
                return NGX_ERROR;
            }

            break;

        /* the first digit of minor HTTP version */
        case sw_first_minor_digit:
            if (ch < '0' || ch > '9') {
                return NGX_ERROR;
            }

            state = sw_minor_digit;
            break;

        /* the minor HTTP version or the end of the request line */
        case sw_minor_digit:
            if (ch == ' ') {
                state = sw_status;
                break;
            }

            if (ch < '0' || ch > '9') {
                return NGX_ERROR;
            }

            break;

        /* HTTP status code */
        case sw_status:
            if (ch == ' ') {
                break;
            }

            if (ch < '0' || ch > '9') {
                return NGX_ERROR;
            }

            status->code = status->code * 10 + ch - '0';

            if (++status->count == 3) {
                state = sw_space_after_status;
                status->start = p - 2;
            }

            break;

        /* space or end of line */
        case sw_space_after_status:
            switch (ch) {
            case ' ':
                state = sw_status_text;
                break;
            case '.':                    /* IIS may send 403.1, 403.2, etc */
                state = sw_status_text;
                break;
            case CR:
                state = sw_almost_done;
                break;
            case LF:
                goto done;
            default:
                return NGX_ERROR;
            }
            break;

        /* any text until end of line */
        case sw_status_text:
            switch (ch) {
            case CR:
                state = sw_almost_done;

                break;
            case LF:
                goto done;
            }
            break;

        /* end of status line */
        case sw_almost_done:
            status->end = p - 1;
            if (ch == LF) {
                goto done;
            } else {
                return NGX_ERROR;
            }
        }
    }

    b->pos = p;
    ctx->state = state;

    return NGX_AGAIN;

done:

    b->pos = p + 1;

    if (status->end == NULL) {
        status->end = p;
    }

    ctx->state = sw_start;

    return NGX_OK;
}