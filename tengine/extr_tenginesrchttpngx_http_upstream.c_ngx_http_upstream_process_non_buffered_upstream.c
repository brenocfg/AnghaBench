#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* connection; } ;
struct TYPE_11__ {TYPE_1__ peer; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_12__ {TYPE_2__* read; TYPE_5__* log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_13__ {char* action; } ;
struct TYPE_10__ {scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_GATEWAY_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_non_buffered_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_upstream_process_non_buffered_upstream(ngx_http_request_t *r,
    ngx_http_upstream_t *u)
{
    ngx_connection_t  *c;

    c = u->peer.connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http upstream process non buffered upstream");

    c->log->action = "reading upstream";

    if (c->read->timedout) {
        ngx_connection_error(c, NGX_ETIMEDOUT, "upstream timed out");
        ngx_http_upstream_finalize_request(r, u, NGX_HTTP_GATEWAY_TIME_OUT);
        return;
    }

    ngx_http_upstream_process_non_buffered_request(r, 0);
}