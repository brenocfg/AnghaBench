#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* read_event_handler ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* write_event_handler ) (TYPE_2__*,TYPE_1__*) ;} ;
typedef  TYPE_1__ ngx_http_upstream_t ;
struct TYPE_13__ {int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_4__* connection; TYPE_1__* upstream; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {scalar_t__ write; scalar_t__ timedout; scalar_t__ delayed; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_set_log_request (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
ngx_http_upstream_handler(ngx_event_t *ev)
{
    ngx_connection_t     *c;
    ngx_http_request_t   *r;
    ngx_http_upstream_t  *u;

    c = ev->data;
    r = c->data;

    u = r->upstream;
    c = r->connection;

    ngx_http_set_log_request(c->log, r);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http upstream request: \"%V?%V\"", &r->uri, &r->args);

    if (ev->delayed && ev->timedout) {
        ev->delayed = 0;
        ev->timedout = 0;
    }

    if (ev->write) {
        u->write_event_handler(r, u);

    } else {
        u->read_event_handler(r, u);
    }

    ngx_http_run_posted_requests(c);
}