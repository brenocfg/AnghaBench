#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_8__ {TYPE_2__* connection; TYPE_1__ request_line; TYPE_4__* cleanup; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ ngx_http_cleanup_t ;
struct TYPE_7__ {int destroyed; int /*<<< orphan*/ * log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ngx_http_lua_free_fake_request(ngx_http_request_t *r)
{
    ngx_log_t                 *log;
    ngx_http_cleanup_t        *cln;

    log = r->connection->log;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, log, 0, "http lua close fake "
                   "request");

    if (r->pool == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, 0, "http lua fake request "
                      "already closed");
        return;
    }

    cln = r->cleanup;
    r->cleanup = NULL;

    while (cln) {
        if (cln->handler) {
            cln->handler(cln->data);
        }

        cln = cln->next;
    }

    r->request_line.len = 0;

    r->connection->destroyed = 1;
}