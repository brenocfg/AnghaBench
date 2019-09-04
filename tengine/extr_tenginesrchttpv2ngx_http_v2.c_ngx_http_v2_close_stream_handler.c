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
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_6__ {scalar_t__ timedout; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_7__ {int timedout; int /*<<< orphan*/  log; TYPE_1__* data; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_http_v2_close_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_v2_close_stream_handler(ngx_event_t *ev)
{
    ngx_connection_t    *fc;
    ngx_http_request_t  *r;

    fc = ev->data;
    r = fc->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 close stream handler");

    if (ev->timedout) {
        ngx_log_error(NGX_LOG_INFO, fc->log, NGX_ETIMEDOUT, "client timed out");

        fc->timedout = 1;

        ngx_http_v2_close_stream(r->stream, NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    ngx_http_v2_close_stream(r->stream, 0);
}