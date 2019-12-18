#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {int header_sent; scalar_t__ (* input_filter_init ) (TYPE_7__*) ;scalar_t__ length; TYPE_7__* input_filter_ctx; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/ * input_filter; int /*<<< orphan*/  buffering; TYPE_2__* conf; TYPE_1__* pipe; int /*<<< orphan*/  store; int /*<<< orphan*/  cacheable; } ;
typedef  TYPE_6__ ngx_http_upstream_t ;
struct TYPE_30__ {scalar_t__ limit_rate; int /*<<< orphan*/  (* write_event_handler ) (TYPE_7__*) ;TYPE_5__* request_body; int /*<<< orphan*/  pool; scalar_t__ header_only; TYPE_9__* connection; scalar_t__ post_action; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_31__ {scalar_t__ tcp_nodelay; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_32__ {scalar_t__ tcp_nodelay; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_28__ {TYPE_4__* temp_file; } ;
struct TYPE_26__ {int /*<<< orphan*/  fd; } ;
struct TYPE_27__ {TYPE_3__ file; } ;
struct TYPE_25__ {int /*<<< orphan*/  preserve_output; } ;
struct TYPE_24__ {int downstream_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_FLUSH ; 
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
 scalar_t__ ngx_http_send_special (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_7__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_http_upstream_non_buffered_filter ; 
 scalar_t__ ngx_http_upstream_non_buffered_filter_init (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_non_buffered_downstream (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_non_buffered_upstream ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_pool_run_cleanup_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 
 scalar_t__ stub1 (TYPE_7__*) ; 

void
ngx_http_multi_upstream_send_response(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    int                        tcp_nodelay;
    ngx_int_t                  rc;
    ngx_connection_t          *c;
    ngx_http_core_loc_conf_t  *clcf;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http multi upstream send response: %p, %p", r, u);

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->post_action) {
        ngx_http_upstream_finalize_request(r, u, rc);
        return;
    }

    u->header_sent = 1;

    c = r->connection;

    if (r->header_only) {

        if (!u->buffering) {
            ngx_http_upstream_finalize_request(r, u, rc);
            return;
        }

        if (!u->cacheable && !u->store) {
            ngx_http_upstream_finalize_request(r, u, rc);
            return;
        }

        u->pipe->downstream_error = 1;
    }

    if (r->request_body && r->request_body->temp_file
            && !u->conf->preserve_output) {
        ngx_pool_run_cleanup_file(r->pool, r->request_body->temp_file->file.fd);
        r->request_body->temp_file->file.fd = NGX_INVALID_FILE;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (!u->buffering) {

        if (u->input_filter == NULL) {
            u->input_filter_init = ngx_http_upstream_non_buffered_filter_init;
            u->input_filter = ngx_http_upstream_non_buffered_filter;
            u->input_filter_ctx = r;
        }

        u->read_event_handler = ngx_http_upstream_process_non_buffered_upstream;
        r->write_event_handler =
                             ngx_http_upstream_process_non_buffered_downstream;

        r->limit_rate = 0;

        if (u->input_filter_init(u->input_filter_ctx) == NGX_ERROR) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }

        if (clcf->tcp_nodelay && c->tcp_nodelay == NGX_TCP_NODELAY_UNSET) {
            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0, "tcp_nodelay");

            tcp_nodelay = 1;

            if (setsockopt(c->fd, IPPROTO_TCP, TCP_NODELAY,
                               (const void *) &tcp_nodelay, sizeof(int)) == -1)
            {
                ngx_connection_error(c, ngx_socket_errno,
                                     "setsockopt(TCP_NODELAY) failed");
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }

            c->tcp_nodelay = NGX_TCP_NODELAY_SET;
        }

        if (u->length == 0) {
            if (ngx_http_send_special(r, NGX_HTTP_FLUSH) == NGX_ERROR) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }

            ngx_http_upstream_process_non_buffered_downstream(r);
        }

        return;
    }
}