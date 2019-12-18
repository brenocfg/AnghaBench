#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {char* data; size_t len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_socket_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; TYPE_1__* connection; scalar_t__ header_sent; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_20__ {scalar_t__ transform_underscores_in_resp_headers; } ;
typedef  TYPE_4__ ngx_http_lua_loc_conf_t ;
struct TYPE_21__ {char* data; size_t len; } ;
typedef  TYPE_5__ ngx_http_lua_ffi_str_t ;
struct TYPE_22__ {int headers_set; scalar_t__ header_sent; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_17__ {scalar_t__ fd; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 
 int NGX_HTTP_LUA_FFI_NO_REQ_CTX ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int,...) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_set_output_header (TYPE_3__*,TYPE_6__*,TYPE_2__,TYPE_2__,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,char const*,size_t) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

int
ngx_http_lua_ffi_set_resp_header(ngx_http_request_t *r, const u_char *key_data,
    size_t key_len, int is_nil, const u_char *sval, size_t sval_len,
    ngx_http_lua_ffi_str_t *mvals, size_t mvals_len, int override,
    char **errmsg)
{
    u_char                      *p;
    ngx_str_t                    value, key;
    ngx_uint_t                   i;
    size_t                       len;
    ngx_http_lua_ctx_t          *ctx;
    ngx_int_t                    rc;
    ngx_http_lua_loc_conf_t     *llcf;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return NGX_HTTP_LUA_FFI_NO_REQ_CTX;
    }

    if (r->connection->fd == (ngx_socket_t) -1) {
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    if (r->header_sent || ctx->header_sent) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "attempt to "
                      "set ngx.header.HEADER after sending out "
                      "response headers");
        return NGX_DECLINED;
    }

    key.data = ngx_palloc(r->pool, key_len + 1);
    if (key.data == NULL) {
        goto nomem;
    }

    ngx_memcpy(key.data, key_data, key_len);
    key.data[key_len] = '\0';
    key.len = key_len;

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (llcf->transform_underscores_in_resp_headers) {
        /* replace "_" with "-" */
        p = key.data;
        for (i = 0; i < key_len; i++) {
            if (p[i] == '_') {
                p[i] = '-';
            }
        }
    }

    ctx->headers_set = 1;

    if (is_nil) {
        value.data = NULL;
        value.len = 0;

    } else if (mvals) {

        if (mvals_len == 0) {
            value.data = NULL;
            value.len = 0;

        } else {
            for (i = 0; i < mvals_len; i++) {
                dd("header value table index %d", (int) i);

                p = mvals[i].data;
                len = mvals[i].len;

                value.data = ngx_palloc(r->pool, len);
                if (value.data == NULL) {
                    goto nomem;
                }

                ngx_memcpy(value.data, p, len);
                value.len = len;

                rc = ngx_http_lua_set_output_header(r, ctx, key, value,
                                                    override && i == 0);

                if (rc == NGX_ERROR) {
                    *errmsg = "failed to set header";
                    return NGX_ERROR;
                }
            }

            return NGX_OK;
        }

    } else {
        p = (u_char *) sval;
        value.data = ngx_palloc(r->pool, sval_len);
        if (value.data == NULL) {
            goto nomem;
        }

        ngx_memcpy(value.data, p, sval_len);
        value.len = sval_len;
    }

    dd("key: %.*s, value: %.*s",
       (int) key.len, key.data, (int) value.len, value.data);

    rc = ngx_http_lua_set_output_header(r, ctx, key, value, override);

    if (rc == NGX_ERROR) {
        *errmsg = "failed to set header";
        return NGX_ERROR;
    }

    return 0;

nomem:

    *errmsg = "no memory";
    return NGX_ERROR;
}