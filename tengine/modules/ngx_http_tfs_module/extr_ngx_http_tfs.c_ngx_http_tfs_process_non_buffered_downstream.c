#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ segment_index; } ;
struct TYPE_16__ {scalar_t__ code; } ;
struct TYPE_17__ {int version; scalar_t__ is_raw_update; TYPE_1__ action; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; TYPE_3__ file; int /*<<< orphan*/  is_rolling_back; int /*<<< orphan*/  state; int /*<<< orphan*/  parent; TYPE_2__ r_ctx; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_20__ {int /*<<< orphan*/  write_event_handler; TYPE_7__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_21__ {scalar_t__ timedout; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_22__ {int timedout; TYPE_8__* log; TYPE_6__* write; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_23__ {char* action; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 scalar_t__ NGX_HTTP_TFS_NO ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_request_empty_handler ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_module ; 
 int /*<<< orphan*/  ngx_http_tfs_process_non_buffered_request (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_tfs_process_non_buffered_downstream(ngx_http_request_t *r)
{
    ngx_event_t       *wev;
    ngx_http_tfs_t    *t;
    ngx_connection_t  *c;

    c = r->connection;
    wev = c->write;
    t = ngx_http_get_module_ctx(r, ngx_http_tfs_module);

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http tfs upstream process downstream");

    c->log->action = "sending to client";

    if (wev->timedout) {
        c->timedout = 1;
        ngx_connection_error(c, NGX_ETIMEDOUT, "client timed out");

        /* write need roll back, remove all segments */
        if (t->r_ctx.version == 1
            && t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE
            && t->r_ctx.is_raw_update == NGX_HTTP_TFS_NO
            && !t->parent)
        {
            r->write_event_handler = ngx_http_request_empty_handler;
            t->state = NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO;
            t->is_rolling_back = NGX_HTTP_TFS_YES;
            t->file.segment_index = 0;
            ngx_http_tfs_finalize_state(t, NGX_OK);
            return;
        }

        ngx_http_tfs_finalize_request(t->data, t,
                                      NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    ngx_http_tfs_process_non_buffered_request(t, 1);
}