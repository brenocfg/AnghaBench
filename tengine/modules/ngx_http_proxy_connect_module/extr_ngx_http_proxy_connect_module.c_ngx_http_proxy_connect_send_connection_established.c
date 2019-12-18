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
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_23__ {int status; } ;
struct TYPE_27__ {int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  (* read_event_handler ) (TYPE_4__*) ;TYPE_2__* header_in; TYPE_1__ headers_out; TYPE_8__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_28__ {int connected; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_32__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_29__ {int send_established; int send_established_done; int /*<<< orphan*/  send_timeout; TYPE_9__ buf; TYPE_5__* u; } ;
typedef  TYPE_6__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_30__ {int /*<<< orphan*/  send_lowat; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_31__ {scalar_t__ (* send ) (TYPE_8__*,scalar_t__,scalar_t__) ;TYPE_20__* write; TYPE_3__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_8__ ngx_connection_t ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_26__ {scalar_t__ ready; } ;
struct TYPE_25__ {scalar_t__ last; scalar_t__ pos; } ;
struct TYPE_24__ {scalar_t__ timer_set; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_20__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_20__*) ; 
 scalar_t__ ngx_handle_write_event (TYPE_20__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_4__*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_read_downstream (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_send_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_write_downstream ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (TYPE_8__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_send_connection_established(ngx_http_request_t *r)
{
    ngx_int_t                              n;
    ngx_buf_t                             *b;
    ngx_connection_t                      *c;
    ngx_http_core_loc_conf_t              *clcf;
    ngx_http_proxy_connect_upstream_t     *u;
    ngx_http_proxy_connect_ctx_t          *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);
    c = r->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: send 200 connection established");

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    u = ctx->u;

    b = &ctx->buf;

    ctx->send_established = 1;
    u->connected = 1;

    for (;;) {
        n = c->send(c, b->pos, b->last - b->pos);

        if (n >= 0) {

            r->headers_out.status = 200;    /* fixed that $status is 000 */

            b->pos += n;

            if (b->pos == b->last) {
                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                              "proxy_connect: sent 200 connection established");

                if (c->write->timer_set) {
                    ngx_del_timer(c->write);
                }

                ctx->send_established_done = 1;

                r->write_event_handler =
                                        ngx_http_proxy_connect_write_downstream;
                r->read_event_handler = ngx_http_proxy_connect_read_downstream;

                if (ngx_handle_write_event(c->write, clcf->send_lowat)
                    != NGX_OK)
                {
                    ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return;
                }

                if (r->header_in->last > r->header_in->pos || c->read->ready) {
                    r->read_event_handler(r);
                    return;
                }

                return;
            }

            /* keep sending more data */
            continue;
        }

        /* NGX_ERROR || NGX_AGAIN */
        break;
    }

    if (n == NGX_ERROR) {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
        return;
    }

    /* n == NGX_AGAIN */
    r->write_event_handler = ngx_http_proxy_connect_send_handler;

    ngx_add_timer(c->write, ctx->send_timeout);

    if (ngx_handle_write_event(c->write, clcf->send_lowat) != NGX_OK) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    return;
}