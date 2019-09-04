#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int max_requests; int /*<<< orphan*/  pool_size; } ;
typedef  TYPE_4__ ngx_http_v2_srv_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pool; TYPE_2__* connection; int /*<<< orphan*/  idle; TYPE_1__* http_connection; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* handler ) (TYPE_6__*) ;scalar_t__ timedout; TYPE_7__* data; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_19__ {TYPE_3__* write; scalar_t__ destroyed; scalar_t__ close; int /*<<< orphan*/  log; TYPE_5__* data; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_15__ {int /*<<< orphan*/  handler; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_NO_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/ * ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_srv_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_finalize_connection (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int /*<<< orphan*/  ngx_http_v2_read_handler (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_v2_write_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_reusable_connection (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_v2_idle_handler(ngx_event_t *rev)
{
    ngx_connection_t          *c;
    ngx_http_v2_srv_conf_t    *h2scf;
    ngx_http_v2_connection_t  *h2c;

    c = rev->data;
    h2c = c->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0, "http2 idle handler");

    if (rev->timedout || c->close) {
        ngx_http_v2_finalize_connection(h2c, NGX_HTTP_V2_NO_ERROR);
        return;
    }

#if (NGX_HAVE_KQUEUE)

    if (ngx_event_flags & NGX_USE_KQUEUE_EVENT) {
        if (rev->pending_eof) {
            c->log->handler = NULL;
            ngx_log_error(NGX_LOG_INFO, c->log, rev->kq_errno,
                          "kevent() reported that client %V closed "
                          "idle connection", &c->addr_text);
#if (NGX_HTTP_SSL)
            if (c->ssl) {
                c->ssl->no_send_shutdown = 1;
            }
#endif
            ngx_http_close_connection(c);
            return;
        }
    }

#endif

    h2scf = ngx_http_get_module_srv_conf(h2c->http_connection->conf_ctx,
                                         ngx_http_v2_module);

    if (h2c->idle++ > 10 * h2scf->max_requests) {
        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "http2 flood detected");
        ngx_http_v2_finalize_connection(h2c, NGX_HTTP_V2_NO_ERROR);
        return;
    }

    c->destroyed = 0;
    ngx_reusable_connection(c, 0);

    h2c->pool = ngx_create_pool(h2scf->pool_size, h2c->connection->log);
    if (h2c->pool == NULL) {
        ngx_http_v2_finalize_connection(h2c, NGX_HTTP_V2_INTERNAL_ERROR);
        return;
    }

    c->write->handler = ngx_http_v2_write_handler;

    rev->handler = ngx_http_v2_read_handler;
    ngx_http_v2_read_handler(rev);
}