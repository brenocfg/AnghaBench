#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_18__ {char* data; int len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_16__ {int len; } ;
struct TYPE_19__ {int output_chosen; int output; void* conditional; TYPE_1__ command; } ;
typedef  TYPE_4__ ngx_http_ssi_ctx_t ;
struct TYPE_20__ {TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_DECLINED ; 
 int NGX_HTTP_SSI_ADD_ZERO ; 
 void* NGX_HTTP_SSI_COND_IF ; 
 int NGX_HTTP_SSI_ERROR ; 
 size_t NGX_HTTP_SSI_IF_EXPR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int NGX_OK ; 
 int ngx_http_ssi_evaluate_string (TYPE_5__*,TYPE_4__*,TYPE_3__*,int) ; 
 int ngx_http_ssi_regex_match (TYPE_5__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_if(ngx_http_request_t *r, ngx_http_ssi_ctx_t *ctx,
    ngx_str_t **params)
{
    u_char       *p, *last;
    ngx_str_t    *expr, left, right;
    ngx_int_t     rc;
    ngx_uint_t    negative, noregex, flags;

    if (ctx->command.len == 2) {
        if (ctx->conditional) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "the \"if\" command inside the \"if\" command");
            return NGX_HTTP_SSI_ERROR;
        }
    }

    if (ctx->output_chosen) {
        ctx->output = 0;
        return NGX_OK;
    }

    expr = params[NGX_HTTP_SSI_IF_EXPR];

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "ssi if expr=\"%V\"", expr);

    left.data = expr->data;
    last = expr->data + expr->len;

    for (p = left.data; p < last; p++) {
        if (*p >= 'A' && *p <= 'Z') {
            *p |= 0x20;
            continue;
        }

        if ((*p >= 'a' && *p <= 'z')
             || (*p >= '0' && *p <= '9')
             || *p == '$' || *p == '{' || *p == '}' || *p == '_'
             || *p == '"' || *p == '\'')
        {
            continue;
        }

        break;
    }

    left.len = p - left.data;

    while (p < last && *p == ' ') {
        p++;
    }

    flags = 0;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "left: \"%V\"", &left);

    rc = ngx_http_ssi_evaluate_string(r, ctx, &left, flags);

    if (rc != NGX_OK) {
        return rc;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "evaluated left: \"%V\"", &left);

    if (p == last) {
        if (left.len) {
            ctx->output = 1;
            ctx->output_chosen = 1;

        } else {
            ctx->output = 0;
        }

        ctx->conditional = NGX_HTTP_SSI_COND_IF;

        return NGX_OK;
    }

    if (p < last && *p == '=') {
        negative = 0;
        p++;

    } else if (p + 1 < last && *p == '!' && *(p + 1) == '=') {
        negative = 1;
        p += 2;

    } else {
        goto invalid_expression;
    }

    while (p < last && *p == ' ') {
        p++;
    }

    if (p < last - 1 && *p == '/') {
        if (*(last - 1) != '/') {
            goto invalid_expression;
        }

        noregex = 0;
        flags = NGX_HTTP_SSI_ADD_ZERO;
        last--;
        p++;

    } else {
        noregex = 1;
        flags = 0;

        if (p < last - 1 && p[0] == '\\' && p[1] == '/') {
            p++;
        }
    }

    right.len = last - p;
    right.data = p;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "right: \"%V\"", &right);

    rc = ngx_http_ssi_evaluate_string(r, ctx, &right, flags);

    if (rc != NGX_OK) {
        return rc;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "evaluated right: \"%V\"", &right);

    if (noregex) {
        if (left.len != right.len) {
            rc = -1;

        } else {
            rc = ngx_strncmp(left.data, right.data, right.len);
        }

    } else {
        right.data[right.len] = '\0';

        rc = ngx_http_ssi_regex_match(r, &right, &left);

        if (rc == NGX_OK) {
            rc = 0;
        } else if (rc == NGX_DECLINED) {
            rc = -1;
        } else {
            return rc;
        }
    }

    if ((rc == 0 && !negative) || (rc != 0 && negative)) {
        ctx->output = 1;
        ctx->output_chosen = 1;

    } else {
        ctx->output = 0;
    }

    ctx->conditional = NGX_HTTP_SSI_COND_IF;

    return NGX_OK;

invalid_expression:

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                  "invalid expression in \"%V\"", expr);

    return NGX_HTTP_SSI_ERROR;
}