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
typedef  char u_char ;
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_6__ {char* data; int len; } ;
struct TYPE_7__ {TYPE_2__ args; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_5__ {scalar_t__ fd; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 
 int NGX_HTTP_LUA_MAX_ARGS ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
ngx_http_lua_ffi_req_get_uri_args_count(ngx_http_request_t *r, int max,
    int *truncated)
{
    int                      count;
    u_char                  *p, *last;

    if (r->connection->fd == (ngx_socket_t) -1) {
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    *truncated = 0;

    if (max < 0) {
        max = NGX_HTTP_LUA_MAX_ARGS;
    }

    last = r->args.data + r->args.len;
    count = 0;

    for (p = r->args.data; p != last; p++) {
        if (*p == '&') {
            if (count == 0) {
                count += 2;

            } else {
                count++;
            }
        }
    }

    if (count) {
        if (max > 0 && count > max) {
            count = max;
            *truncated = 1;
            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "lua hit query args limit %d", max);
        }

        return count;
    }

    if (r->args.len) {
        return 1;
    }

    return 0;
}