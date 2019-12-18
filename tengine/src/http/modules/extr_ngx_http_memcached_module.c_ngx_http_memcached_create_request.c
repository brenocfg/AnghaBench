#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_21__ {int len; int /*<<< orphan*/  data; scalar_t__ not_found; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_22__ {TYPE_2__* connection; TYPE_1__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_23__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_5__ ngx_http_memcached_loc_conf_t ;
struct TYPE_27__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {TYPE_9__ key; } ;
typedef  TYPE_6__ ngx_http_memcached_ctx_t ;
struct TYPE_25__ {int /*<<< orphan*/ * next; TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_26__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;
struct TYPE_19__ {TYPE_7__* request_bufs; } ;
typedef  int /*<<< orphan*/  CRLF ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  LF ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ESCAPE_MEMCACHED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int ngx_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_indexed_variable (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_memcached_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_memcached_create_request(ngx_http_request_t *r)
{
    size_t                          len;
    uintptr_t                       escape;
    ngx_buf_t                      *b;
    ngx_chain_t                    *cl;
    ngx_http_memcached_ctx_t       *ctx;
    ngx_http_variable_value_t      *vv;
    ngx_http_memcached_loc_conf_t  *mlcf;

    mlcf = ngx_http_get_module_loc_conf(r, ngx_http_memcached_module);

    vv = ngx_http_get_indexed_variable(r, mlcf->index);

    if (vv == NULL || vv->not_found || vv->len == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "the \"$memcached_key\" variable is not set");
        return NGX_ERROR;
    }

    escape = 2 * ngx_escape_uri(NULL, vv->data, vv->len, NGX_ESCAPE_MEMCACHED);

    len = sizeof("get ") - 1 + vv->len + escape + sizeof(CRLF) - 1;

    b = ngx_create_temp_buf(r->pool, len);
    if (b == NULL) {
        return NGX_ERROR;
    }

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf = b;
    cl->next = NULL;

    r->upstream->request_bufs = cl;

    *b->last++ = 'g'; *b->last++ = 'e'; *b->last++ = 't'; *b->last++ = ' ';

    ctx = ngx_http_get_module_ctx(r, ngx_http_memcached_module);

    ctx->key.data = b->last;

    if (escape == 0) {
        b->last = ngx_copy(b->last, vv->data, vv->len);

    } else {
        b->last = (u_char *) ngx_escape_uri(b->last, vv->data, vv->len,
                                            NGX_ESCAPE_MEMCACHED);
    }

    ctx->key.len = b->last - ctx->key.data;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http memcached request: \"%V\"", &ctx->key);

    *b->last++ = CR; *b->last++ = LF;

    return NGX_OK;
}