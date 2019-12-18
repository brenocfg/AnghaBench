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
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  char u_char ;
typedef  char off_t ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {char content_length_n; } ;
struct TYPE_18__ {TYPE_2__* range; } ;
struct TYPE_20__ {TYPE_4__ headers_out; TYPE_3__ headers_in; int /*<<< orphan*/  pool; struct TYPE_20__* main; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_21__ {char start; char end; } ;
typedef  TYPE_6__ ngx_http_range_t ;
struct TYPE_15__ {scalar_t__ nelts; } ;
struct TYPE_22__ {TYPE_13__ ranges; } ;
typedef  TYPE_7__ ngx_http_range_filter_ctx_t ;
struct TYPE_16__ {char* data; } ;
struct TYPE_17__ {TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_RANGE_NOT_SATISFIABLE ; 
 int NGX_MAX_OFF_T_VALUE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_13__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_6__* ngx_array_push (TYPE_13__*) ; 
 TYPE_7__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_range_body_filter_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_range_parse(ngx_http_request_t *r, ngx_http_range_filter_ctx_t *ctx,
    ngx_uint_t ranges)
{
    u_char                       *p;
    off_t                         start, end, size, content_length, cutoff,
                                  cutlim;
    ngx_uint_t                    suffix;
    ngx_http_range_t             *range;
    ngx_http_range_filter_ctx_t  *mctx;

    if (r != r->main) {
        mctx = ngx_http_get_module_ctx(r->main,
                                       ngx_http_range_body_filter_module);
        if (mctx) {
            ctx->ranges = mctx->ranges;
            return NGX_OK;
        }
    }

    if (ngx_array_init(&ctx->ranges, r->pool, 1, sizeof(ngx_http_range_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    p = r->headers_in.range->value.data + 6;
    size = 0;
    content_length = r->headers_out.content_length_n;

    cutoff = NGX_MAX_OFF_T_VALUE / 10;
    cutlim = NGX_MAX_OFF_T_VALUE % 10;

    for ( ;; ) {
        start = 0;
        end = 0;
        suffix = 0;

        while (*p == ' ') { p++; }

        if (*p != '-') {
            if (*p < '0' || *p > '9') {
                return NGX_HTTP_RANGE_NOT_SATISFIABLE;
            }

            while (*p >= '0' && *p <= '9') {
                if (start >= cutoff && (start > cutoff || *p - '0' > cutlim)) {
                    return NGX_HTTP_RANGE_NOT_SATISFIABLE;
                }

                start = start * 10 + (*p++ - '0');
            }

            while (*p == ' ') { p++; }

            if (*p++ != '-') {
                return NGX_HTTP_RANGE_NOT_SATISFIABLE;
            }

            while (*p == ' ') { p++; }

            if (*p == ',' || *p == '\0') {
                end = content_length;
                goto found;
            }

        } else {
            suffix = 1;
            p++;
        }

        if (*p < '0' || *p > '9') {
            return NGX_HTTP_RANGE_NOT_SATISFIABLE;
        }

        while (*p >= '0' && *p <= '9') {
            if (end >= cutoff && (end > cutoff || *p - '0' > cutlim)) {
                return NGX_HTTP_RANGE_NOT_SATISFIABLE;
            }

            end = end * 10 + (*p++ - '0');
        }

        while (*p == ' ') { p++; }

        if (*p != ',' && *p != '\0') {
            return NGX_HTTP_RANGE_NOT_SATISFIABLE;
        }

        if (suffix) {
            start = (end < content_length) ? content_length - end : 0;
            end = content_length - 1;
        }

        if (end >= content_length) {
            end = content_length;

        } else {
            end++;
        }

    found:

        if (start < end) {
            range = ngx_array_push(&ctx->ranges);
            if (range == NULL) {
                return NGX_ERROR;
            }

            range->start = start;
            range->end = end;

            if (size > NGX_MAX_OFF_T_VALUE - (end - start)) {
                return NGX_HTTP_RANGE_NOT_SATISFIABLE;
            }

            size += end - start;

            if (ranges-- == 0) {
                return NGX_DECLINED;
            }

        } else if (start == 0) {
            return NGX_DECLINED;
        }

        if (*p++ != ',') {
            break;
        }
    }

    if (ctx->ranges.nelts == 0) {
        return NGX_HTTP_RANGE_NOT_SATISFIABLE;
    }

    if (size > content_length) {
        return NGX_DECLINED;
    }

    return NGX_OK;
}