#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ timedout; int /*<<< orphan*/  write; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_12__ {TYPE_2__* ssl; TYPE_1__* async; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* handler ) (TYPE_4__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ssl_empty_handler ; 
 scalar_t__ ngx_ssl_handshake (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

__attribute__((used)) static void
ngx_ssl_handshake_handler(ngx_event_t *ev)
{
    ngx_connection_t  *c;

    c = ev->data;

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "SSL handshake handler: %d", ev->write);

    if (ev->timedout) {
        c->ssl->handler(c);
        return;
    }

    if (ngx_ssl_handshake(c) == NGX_AGAIN) {
        return;
    }

#if (NGX_SSL && NGX_SSL_ASYNC)
    /*
     * empty the handler of async event to avoid
     * going back to previous ssl handshake state
     */
    c->async->handler = ngx_ssl_empty_handler;
#endif
    c->ssl->handler(c);
}