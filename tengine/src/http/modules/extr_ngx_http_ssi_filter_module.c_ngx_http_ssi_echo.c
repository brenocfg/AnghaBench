#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_24__ {scalar_t__ len; int /*<<< orphan*/ * data; int /*<<< orphan*/  not_found; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_25__ {int encoding; TYPE_6__** last_out; } ;
typedef  TYPE_4__ ngx_http_ssi_ctx_t ;
struct TYPE_26__ {int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_27__ {struct TYPE_27__* next; TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_28__ {int memory; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ESCAPE_HTML ; 
 size_t NGX_HTTP_SSI_ECHO_DEFAULT ; 
 size_t NGX_HTTP_SSI_ECHO_ENCODING ; 
 size_t NGX_HTTP_SSI_ECHO_VAR ; 
#define  NGX_HTTP_SSI_ENTITY_ENCODING 129 
 int /*<<< orphan*/  NGX_HTTP_SSI_ERROR ; 
 int NGX_HTTP_SSI_NO_ENCODING ; 
#define  NGX_HTTP_SSI_URL_ENCODING 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 uintptr_t ngx_escape_html (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ngx_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__* ngx_http_get_variable (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_ssi_get_variable (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ ngx_http_ssi_none ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_echo(ngx_http_request_t *r, ngx_http_ssi_ctx_t *ctx,
    ngx_str_t **params)
{
    u_char                     *p;
    uintptr_t                   len;
    ngx_buf_t                  *b;
    ngx_str_t                  *var, *value, *enc, text;
    ngx_uint_t                  key;
    ngx_chain_t                *cl;
    ngx_http_variable_value_t  *vv;

    var = params[NGX_HTTP_SSI_ECHO_VAR];

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "ssi echo \"%V\"", var);

    key = ngx_hash_strlow(var->data, var->data, var->len);

    value = ngx_http_ssi_get_variable(r, var, key);

    if (value == NULL) {
        vv = ngx_http_get_variable(r, var, key);

        if (vv == NULL) {
            return NGX_HTTP_SSI_ERROR;
        }

        if (!vv->not_found) {
            text.data = vv->data;
            text.len = vv->len;
            value = &text;
        }
    }

    if (value == NULL) {
        value = params[NGX_HTTP_SSI_ECHO_DEFAULT];

        if (value == NULL) {
            value = &ngx_http_ssi_none;

        } else if (value->len == 0) {
            return NGX_OK;
        }

    } else {
        if (value->len == 0) {
            return NGX_OK;
        }
    }

    enc = params[NGX_HTTP_SSI_ECHO_ENCODING];

    if (enc) {
        if (enc->len == 4 && ngx_strncmp(enc->data, "none", 4) == 0) {

            ctx->encoding = NGX_HTTP_SSI_NO_ENCODING;

        } else if (enc->len == 3 && ngx_strncmp(enc->data, "url", 3) == 0) {

            ctx->encoding = NGX_HTTP_SSI_URL_ENCODING;

        } else if (enc->len == 6 && ngx_strncmp(enc->data, "entity", 6) == 0) {

            ctx->encoding = NGX_HTTP_SSI_ENTITY_ENCODING;

        } else {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "unknown encoding \"%V\" in the \"echo\" command",
                          enc);
        }
    }

    p = value->data;

    switch (ctx->encoding) {

    case NGX_HTTP_SSI_URL_ENCODING:
        len = 2 * ngx_escape_uri(NULL, value->data, value->len,
                                 NGX_ESCAPE_HTML);

        if (len) {
            p = ngx_pnalloc(r->pool, value->len + len);
            if (p == NULL) {
                return NGX_HTTP_SSI_ERROR;
            }

            (void) ngx_escape_uri(p, value->data, value->len, NGX_ESCAPE_HTML);
        }

        len += value->len;
        break;

    case NGX_HTTP_SSI_ENTITY_ENCODING:
        len = ngx_escape_html(NULL, value->data, value->len);

        if (len) {
            p = ngx_pnalloc(r->pool, value->len + len);
            if (p == NULL) {
                return NGX_HTTP_SSI_ERROR;
            }

            (void) ngx_escape_html(p, value->data, value->len);
        }

        len += value->len;
        break;

    default: /* NGX_HTTP_SSI_NO_ENCODING */
        len = value->len;
        break;
    }

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_HTTP_SSI_ERROR;
    }

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_HTTP_SSI_ERROR;
    }

    b->memory = 1;
    b->pos = p;
    b->last = p + len;

    cl->buf = b;
    cl->next = NULL;
    *ctx->last_out = cl;
    ctx->last_out = &cl->next;

    return NGX_OK;
}