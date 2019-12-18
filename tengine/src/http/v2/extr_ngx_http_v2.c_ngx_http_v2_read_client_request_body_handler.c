#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* stream; TYPE_4__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_10__ {int timedout; int /*<<< orphan*/  log; scalar_t__ error; TYPE_2__* read; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_8__ {scalar_t__ timedout; } ;
struct TYPE_7__ {int skip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_v2_read_client_request_body_handler(ngx_http_request_t *r)
{
    ngx_connection_t  *fc;

    fc = r->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 read client request body handler");

    if (fc->read->timedout) {
        ngx_log_error(NGX_LOG_INFO, fc->log, NGX_ETIMEDOUT, "client timed out");

        fc->timedout = 1;
        r->stream->skip_data = 1;

        ngx_http_finalize_request(r, NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    if (fc->error) {
        ngx_log_error(NGX_LOG_INFO, fc->log, 0,
                      "client prematurely closed stream");

        r->stream->skip_data = 1;

        ngx_http_finalize_request(r, NGX_HTTP_CLIENT_CLOSED_REQUEST);
        return;
    }
}