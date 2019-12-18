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
struct TYPE_9__ {size_t length; } ;
struct TYPE_10__ {TYPE_2__ state; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_http_v2_state_complete (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_save (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_skip(ngx_http_v2_connection_t *h2c, u_char *pos, u_char *end)
{
    size_t  size;

    size = end - pos;

    if (size < h2c->state.length) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                       "http2 frame skip %uz of %uz", size, h2c->state.length);

        h2c->state.length -= size;
        return ngx_http_v2_state_save(h2c, end, end, ngx_http_v2_state_skip);
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 frame skip %uz", h2c->state.length);

    return ngx_http_v2_state_complete(h2c, pos + h2c->state.length, end);
}