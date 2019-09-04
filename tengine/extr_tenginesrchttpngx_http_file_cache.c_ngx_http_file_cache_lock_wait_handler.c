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
struct TYPE_8__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_3__* connection; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_9__ {TYPE_1__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_file_cache_lock_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_set_log_request (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_file_cache_lock_wait_handler(ngx_event_t *ev)
{
    ngx_connection_t    *c;
    ngx_http_request_t  *r;

    r = ev->data;
    c = r->connection;

    ngx_http_set_log_request(c->log, r);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http file cache wait: \"%V?%V\"", &r->uri, &r->args);

    ngx_http_file_cache_lock_wait(r, r->cache);

    ngx_http_run_posted_requests(c);
}