#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {char* data; size_t len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_10__ {scalar_t__ http_version; int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_8__ {scalar_t__ fd; } ;

/* Variables and functions */
 int NGX_DECLINED ; 
 int NGX_ERROR ; 
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 
 scalar_t__ NGX_HTTP_VERSION_10 ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_lua_set_input_header (TYPE_3__*,TYPE_2__,TYPE_2__,int) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

int
ngx_http_lua_ffi_req_header_set_single_value(ngx_http_request_t *r,
    const u_char *key, size_t key_len, const u_char *value, size_t value_len)
{
    ngx_str_t                    k;
    ngx_str_t                    v;

    if (r->connection->fd == (ngx_socket_t) -1) {  /* fake request */
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    if (r->http_version < NGX_HTTP_VERSION_10) {
        return NGX_DECLINED;
    }

    k.data = ngx_palloc(r->pool, key_len + 1);
    if (k.data == NULL) {
        return NGX_ERROR;
    }
    ngx_memcpy(k.data, key, key_len);
    k.data[key_len] = '\0';

    k.len = key_len;

    if (value_len == 0) {
        v.data = NULL;
        v.len = 0;

    } else {
        v.data = ngx_palloc(r->pool, value_len + 1);
        if (v.data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(v.data, value, value_len);
        v.data[value_len] = '\0';
    }

    v.len = value_len;

    if (ngx_http_lua_set_input_header(r, k, v, 1 /* override */)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}