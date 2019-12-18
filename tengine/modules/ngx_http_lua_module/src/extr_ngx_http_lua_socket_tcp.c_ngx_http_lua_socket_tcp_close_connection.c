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
struct TYPE_7__ {int /*<<< orphan*/ * pool; TYPE_1__* ssl; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_6__ {int no_wait_shutdown; int no_send_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_close_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_ssl_shutdown (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_close_connection(ngx_connection_t *c)
{
#if (NGX_HTTP_SSL)

    if (c->ssl) {
        c->ssl->no_wait_shutdown = 1;
        c->ssl->no_send_shutdown = 1;

        (void) ngx_ssl_shutdown(c);
    }

#endif

    if (c->pool) {
        ngx_destroy_pool(c->pool);
        c->pool = NULL;
    }

    ngx_close_connection(c);
}