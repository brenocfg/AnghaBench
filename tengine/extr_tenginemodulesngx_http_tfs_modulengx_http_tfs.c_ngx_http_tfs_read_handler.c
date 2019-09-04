#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* tfs_peer; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_5__* connection; } ;
struct TYPE_15__ {int /*<<< orphan*/  peer_addr_text; TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_tfs_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_16__ {TYPE_6__* log; TYPE_1__* read; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_17__ {char* action; } ;
struct TYPE_12__ {scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_tfs_handle_connection_failure (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_process_upstream_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_tfs_read_handler(ngx_http_request_t *r, ngx_http_tfs_t *t)
{
    ngx_connection_t               *c;
    ngx_http_tfs_peer_connection_t *tp;

    tp = t->tfs_peer;
    c = tp->peer.connection;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http tfs process tfs(%V) data", tp->peer.name);

    c->log->action = "reading response header from tfs";

    if (c->read->timedout) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "read from (%V: %s) timeout", tp->peer.name,
                      tp->peer_addr_text);
        ngx_http_tfs_handle_connection_failure(t, tp);
        return;
    }

    ngx_http_tfs_process_upstream_request(r, t);
}