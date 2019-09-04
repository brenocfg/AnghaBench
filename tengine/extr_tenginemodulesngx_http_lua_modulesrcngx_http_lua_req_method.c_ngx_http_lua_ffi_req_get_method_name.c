#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_2__ method_name; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_5__ {scalar_t__ fd; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 
 int NGX_OK ; 

int
ngx_http_lua_ffi_req_get_method_name(ngx_http_request_t *r, u_char **name,
    size_t *len)
{
    if (r->connection->fd == (ngx_socket_t) -1) {
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    *name = r->method_name.data;
    *len = r->method_name.len;

    return NGX_OK;
}