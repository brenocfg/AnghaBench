#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {scalar_t__ status; } ;
struct TYPE_13__ {scalar_t__ write_event_handler; int /*<<< orphan*/ * posted_requests; TYPE_2__* connection; scalar_t__ blocked; int /*<<< orphan*/  count; TYPE_5__* cleanup; TYPE_1__ headers_out; struct TYPE_13__* main; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/  terminal_posted_request; } ;
typedef  TYPE_4__ ngx_http_ephemeral_t ;
struct TYPE_15__ {struct TYPE_15__* next; int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ ngx_http_cleanup_t ;
struct TYPE_12__ {scalar_t__ sent; int error; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_close_request (TYPE_3__*,scalar_t__) ; 
 TYPE_4__* ngx_http_ephemeral (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_post_request (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_request_finalizer ; 
 scalar_t__ ngx_http_terminate_handler ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_terminate_request(ngx_http_request_t *r, ngx_int_t rc)
{
    ngx_http_cleanup_t    *cln;
    ngx_http_request_t    *mr;
    ngx_http_ephemeral_t  *e;

    mr = r->main;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http terminate request count:%d", mr->count);

    if (rc > 0 && (mr->headers_out.status == 0 || mr->connection->sent == 0)) {
        mr->headers_out.status = rc;
    }

    cln = mr->cleanup;
    mr->cleanup = NULL;

    while (cln) {
        if (cln->handler) {
            cln->handler(cln->data);
        }

        cln = cln->next;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http terminate cleanup count:%d blk:%d",
                   mr->count, mr->blocked);

    if (mr->write_event_handler) {

        if (mr->blocked) {
            r->connection->error = 1;
            r->write_event_handler = ngx_http_request_finalizer;
            return;
        }

        e = ngx_http_ephemeral(mr);
        mr->posted_requests = NULL;
        mr->write_event_handler = ngx_http_terminate_handler;
        (void) ngx_http_post_request(mr, &e->terminal_posted_request);
        return;
    }

    ngx_http_close_request(mr, rc);
}