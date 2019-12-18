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
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int keep_alive_n; scalar_t__ connection_type; } ;
struct TYPE_10__ {TYPE_1__ headers_in; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_header_val_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_CONNECTION_CLOSE ; 
 scalar_t__ NGX_HTTP_CONNECTION_KEEP_ALIVE ; 
 int /*<<< orphan*/  ngx_http_set_builtin_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ngx_strcasestrn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_connection_header(ngx_http_request_t *r,
    ngx_http_lua_header_val_t *hv, ngx_str_t *value)
{
    r->headers_in.connection_type = 0;

    if (value->len == 0) {
        return ngx_http_set_builtin_header(r, hv, value);
    }

    if (ngx_strcasestrn(value->data, "close", 5 - 1)) {
        r->headers_in.connection_type = NGX_HTTP_CONNECTION_CLOSE;
        r->headers_in.keep_alive_n = -1;

    } else if (ngx_strcasestrn(value->data, "keep-alive", 10 - 1)) {
        r->headers_in.connection_type = NGX_HTTP_CONNECTION_KEEP_ALIVE;
    }

    return ngx_http_set_builtin_header(r, hv, value);
}