#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_24__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_9__* connection; int /*<<< orphan*/  get; int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_4__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_32__ {int /*<<< orphan*/  host; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_5__ ngx_http_upstream_resolved_t ;
struct TYPE_33__ {TYPE_2__* connection; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_34__ {int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  write_event_handler; TYPE_4__ peer; TYPE_5__* resolved; TYPE_1__* conf; } ;
typedef  TYPE_7__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_35__ {int /*<<< orphan*/  connect_timeout; } ;
typedef  TYPE_8__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_36__ {TYPE_24__* write; TYPE_10__* log; TYPE_3__* read; TYPE_22__* pool; int /*<<< orphan*/  sendfile; TYPE_7__* data; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_30__ {TYPE_10__* log; void* handler; } ;
struct TYPE_29__ {TYPE_10__* log; int /*<<< orphan*/  sendfile; } ;
struct TYPE_28__ {TYPE_10__* log; void* handler; } ;
struct TYPE_27__ {TYPE_10__* log; } ;
struct TYPE_26__ {int /*<<< orphan*/  local; } ;
struct TYPE_25__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_24__*,int /*<<< orphan*/ ) ; 
 TYPE_22__* ngx_create_pool (int,TYPE_10__*) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_4__*) ; 
 TYPE_8__* ngx_http_get_module_ctx (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_get_peer ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_read_upstream ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_send_connection_established (TYPE_6__*) ; 
 scalar_t__ ngx_http_proxy_connect_set_local (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_proxy_connect_upstream_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_write_upstream ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_process_connect(ngx_http_request_t *r,
    ngx_http_proxy_connect_upstream_t *u)
{
    ngx_int_t                        rc;
    ngx_connection_t                *c;
    ngx_peer_connection_t           *pc;
    ngx_http_upstream_resolved_t    *ur;
    ngx_http_proxy_connect_ctx_t    *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    r->connection->log->action = "connecting to upstream";

    if (ngx_http_proxy_connect_set_local(r, u, u->conf->local) != NGX_OK) {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    pc = &u->peer;
    ur = u->resolved;

    pc->sockaddr = ur->sockaddr;
    pc->socklen = ur->socklen;
    pc->name = &ur->host;

    pc->get = ngx_http_proxy_connect_get_peer;

    rc = ngx_event_connect_peer(&u->peer);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: ngx_event_connect_peer() returns %i", rc);

    if (rc == NGX_ERROR) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    if (rc == NGX_BUSY) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "proxy_connect: no live connection");
        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        return;
    }

    if (rc == NGX_DECLINED) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "proxy_connect: connection error");
        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        return;
    }

    /* rc == NGX_OK || rc == NGX_AGAIN || rc == NGX_DONE */

    c = pc->connection;

    c->data = u;

    c->write->handler = ngx_http_proxy_connect_upstream_handler;
    c->read->handler = ngx_http_proxy_connect_upstream_handler;

    u->write_event_handler = ngx_http_proxy_connect_write_upstream;
    u->read_event_handler = ngx_http_proxy_connect_read_upstream;

    c->sendfile &= r->connection->sendfile;
    c->log = r->connection->log;

    if (c->pool == NULL) {

        c->pool = ngx_create_pool(128, r->connection->log);
        if (c->pool == NULL) {
            ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }
    }

    c->pool->log = c->log;
    c->read->log = c->log;
    c->write->log = c->log;

    if (rc == NGX_AGAIN) {
        ngx_add_timer(c->write, ctx->connect_timeout);
        return;
    }

    ngx_http_proxy_connect_send_connection_established(r);
}