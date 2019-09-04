#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_7__ {TYPE_1__* buf_in; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_8__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_3__ ngx_buf_t ;
struct TYPE_6__ {TYPE_3__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int,int,...) ; 
 scalar_t__ ngx_http_lua_socket_insert_buffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_add_pending_data(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, u_char *pos, size_t len, u_char *pat,
    int prefix, int old_state)
{
    u_char          *last;
    ngx_buf_t       *b;

    dd("resuming data: %d: [%.*s]", prefix, prefix, pat);

    last = &pos[len];

    b = u->buf_in->buf;

    if (last - b->last == old_state) {
        b->last += prefix;
        return NGX_OK;
    }

    dd("need more buffers because %d != %d", (int) (last - b->last),
       (int) old_state);

    if (ngx_http_lua_socket_insert_buffer(r, u, pat, prefix) != NGX_OK) {
        return NGX_ERROR;
    }

    b->pos = last;
    b->last = last;

    return NGX_OK;
}