#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_23__ {scalar_t__ code; } ;
struct TYPE_24__ {TYPE_1__ action; } ;
struct TYPE_28__ {scalar_t__ tfs_status; scalar_t__ sp_curr; int header_sent; scalar_t__ header_only; struct TYPE_28__* parent; int /*<<< orphan*/  log; int /*<<< orphan*/  sp_ready; TYPE_2__ r_ctx; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
struct TYPE_29__ {scalar_t__ limit_rate; int /*<<< orphan*/  (* write_event_handler ) (TYPE_7__*) ;TYPE_5__* request_body; int /*<<< orphan*/  pool; TYPE_9__* connection; scalar_t__ post_action; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_30__ {scalar_t__ tcp_nodelay; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_31__ {scalar_t__ tcp_nodelay; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_27__ {TYPE_4__* temp_file; } ;
struct TYPE_25__ {int /*<<< orphan*/  fd; } ;
struct TYPE_26__ {TYPE_3__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_READ_FILE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_TCP_NODELAY_SET ; 
 scalar_t__ NGX_TCP_NODELAY_UNSET ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_send_header (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (TYPE_7__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_module ; 
 int /*<<< orphan*/  ngx_http_tfs_process_non_buffered_downstream (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_set_header_line (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_pool_run_cleanup_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void
ngx_http_tfs_send_response(ngx_http_request_t *r, ngx_http_tfs_t *t)
{
    int                        tcp_nodelay;
    ngx_int_t                  rc;
    ngx_http_tfs_t            *parent_tfs;
    ngx_connection_t          *c;
    ngx_http_core_loc_conf_t  *clcf;

    /* sub process */
    if (t->parent) {
        if (t->tfs_status != NGX_OK) {
            ngx_http_tfs_finalize_request(r, t, NGX_ERROR);
            return;
        }

        if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
            ngx_http_tfs_finalize_request(r, t, NGX_DONE);
            return;
        }

        if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE) {
            /* output in the right turn */
            if (t->parent->sp_curr != t->sp_curr) {
                t->sp_ready = NGX_HTTP_TFS_YES;
                ngx_log_debug2(NGX_LOG_DEBUG_HTTP, t->log, 0,
                               "curr output segment is [%uD], "
                               "[%uD] is ready, wait for call...",
                               t->parent->sp_curr, t->sp_curr);
                return;
            }
            /* set ctx */
            ngx_http_set_ctx(r, t, ngx_http_tfs_module);
            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                           "segment[%uD] output...",
                           t->sp_curr);
        }
    }

    if (t->parent == NULL) {
        parent_tfs = t;

    } else {
        parent_tfs = t->parent;
    }

    if (!parent_tfs->header_sent) {
        ngx_http_tfs_set_header_line(t);

        rc = ngx_http_send_header(r);

        if (rc == NGX_ERROR || rc > NGX_OK || r->post_action) {
            ngx_http_tfs_finalize_state(t, rc);
            return;
        }

        parent_tfs->header_sent = 1;

        if (t->header_only) {
            ngx_http_tfs_finalize_request(r, t, rc);
            return;
        }
    }

    c = r->connection;

    if (r->request_body && r->request_body->temp_file) {
        ngx_pool_run_cleanup_file(r->pool, r->request_body->temp_file->file.fd);
        r->request_body->temp_file->file.fd = NGX_INVALID_FILE;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    r->write_event_handler = ngx_http_tfs_process_non_buffered_downstream;

    r->limit_rate = 0;

    if (clcf->tcp_nodelay && c->tcp_nodelay == NGX_TCP_NODELAY_UNSET) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0, "tcp_nodelay");

        tcp_nodelay = 1;

        if (setsockopt(c->fd, IPPROTO_TCP, TCP_NODELAY,
                (const void *) &tcp_nodelay, sizeof(int)) == -1)
        {
            ngx_connection_error(c, ngx_socket_errno,
                                 "setsockopt(TCP_NODELAY) failed");

            ngx_http_tfs_finalize_request(r, t, 0);
            return;
        }

        c->tcp_nodelay = NGX_TCP_NODELAY_SET;
    }

    ngx_http_tfs_process_non_buffered_downstream(r);
    return;
}