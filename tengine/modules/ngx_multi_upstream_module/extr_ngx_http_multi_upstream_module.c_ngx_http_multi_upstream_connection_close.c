#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int destroyed; scalar_t__ pool; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; TYPE_1__* ssl; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_6__ {int no_wait_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ssl_shutdown (TYPE_2__*) ; 

ngx_int_t
ngx_http_multi_upstream_connection_close(ngx_connection_t *c)
{
#if (NGX_HTTP_SSL)
    /* TODO: do not shutdown persistent connection */
    if (c->ssl) {

        /*
         * We send the "close notify" shutdown alert to the upstream only
         * and do not wait its "close notify" shutdown alert.
         * It is acceptable according to the TLS standard.
         */

        c->ssl->no_wait_shutdown = 1;

        (void) ngx_ssl_shutdown(c);
    }
#endif

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
            "multi: close http upstream connection: %d", c->fd);

    if (c->pool) {
        ngx_destroy_pool(c->pool);
    }

    c->destroyed = 1;

    ngx_close_connection(c);

    return NGX_OK;
}