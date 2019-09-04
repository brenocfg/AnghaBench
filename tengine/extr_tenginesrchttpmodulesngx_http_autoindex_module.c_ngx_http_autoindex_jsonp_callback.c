#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_10__ {int len; int* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_arg (TYPE_3__*,int*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_autoindex_jsonp_callback(ngx_http_request_t *r, ngx_str_t *callback)
{
    u_char      *p, c, ch;
    ngx_uint_t   i;

    if (ngx_http_arg(r, (u_char *) "callback", 8, callback) != NGX_OK) {
        callback->len = 0;
        return NGX_OK;
    }

    if (callback->len > 128) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent too long callback name: \"%V\"", callback);
        return NGX_DECLINED;
    }

    p = callback->data;

    for (i = 0; i < callback->len; i++) {
        ch = p[i];

        c = (u_char) (ch | 0x20);
        if (c >= 'a' && c <= 'z') {
            continue;
        }

        if ((ch >= '0' && ch <= '9') || ch == '_' || ch == '.') {
            continue;
        }

        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent invalid callback name: \"%V\"", callback);

        return NGX_DECLINED;
    }

    return NGX_OK;
}