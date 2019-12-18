#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {scalar_t__ code; int /*<<< orphan*/  msg; } ;
struct TYPE_22__ {TYPE_5__ action; } ;
struct TYPE_23__ {scalar_t__ state; scalar_t__ (* process_request_body ) (TYPE_7__*) ;TYPE_6__ r_ctx; int /*<<< orphan*/  log; TYPE_8__* data; TYPE_4__* tfs_peer; } ;
typedef  TYPE_7__ ngx_http_tfs_t ;
struct TYPE_24__ {TYPE_1__* connection; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_19__ {TYPE_2__* connection; int /*<<< orphan*/  name; } ;
struct TYPE_20__ {TYPE_3__ peer; } ;
struct TYPE_18__ {int /*<<< orphan*/  read; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_READ_FILE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_READ_READ_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_handle_read_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_send_response (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (TYPE_7__*) ; 

__attribute__((used)) static void
ngx_http_tfs_process_buf_overflow(ngx_http_request_t *r, ngx_http_tfs_t *t)
{
    ngx_int_t  rc;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                  "tfs process buf overflow, %V", t->tfs_peer->peer.name);

    if ((t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE
         && t->state == NGX_HTTP_TFS_STATE_READ_READ_DATA))
    {
        rc = t->process_request_body(t);

        if (rc != NGX_AGAIN) {
            if (rc == NGX_ERROR) {
                ngx_log_error(NGX_LOG_ERR, t->log, 0,
                              "process request body failed");
                ngx_http_tfs_finalize_request(t->data, t,
                                              NGX_HTTP_INTERNAL_SERVER_ERROR);

            } else {
                ngx_http_tfs_finalize_state(t, rc);
            }
            return;
        }

        if (ngx_handle_read_event(t->tfs_peer->peer.connection->read, 0)
            != NGX_OK)
        {
            ngx_log_error(NGX_LOG_ERR, t->log, 0,
                          "ngx handle read event failed");
            ngx_http_tfs_finalize_request(t->data, t,
                                          NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        ngx_http_tfs_send_response(r, t);

        return;

    }

    ngx_log_error(NGX_LOG_ERR, t->log, 0,
                  "action: %V should not come to here process buf overflow",
                  &t->r_ctx.action.msg);

    ngx_http_tfs_finalize_request(r, t, NGX_HTTP_INTERNAL_SERVER_ERROR);
}