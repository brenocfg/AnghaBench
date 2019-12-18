#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  check_timeout; } ;
typedef  TYPE_3__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; TYPE_6__* connection; scalar_t__ cached; int /*<<< orphan*/  log_error; int /*<<< orphan*/  get; int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_18__ {int /*<<< orphan*/  check_timeout_ev; int /*<<< orphan*/  recv_handler; int /*<<< orphan*/  (* send_handler ) (TYPE_7__*) ;int /*<<< orphan*/  state; int /*<<< orphan*/  pool; TYPE_8__ pc; TYPE_1__* check_peer_addr; TYPE_3__* conf; } ;
typedef  TYPE_4__ ngx_http_upstream_check_peer_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; TYPE_4__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_20__ {TYPE_7__* write; TYPE_2__* read; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; scalar_t__ sendfile; TYPE_4__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_21__ {int /*<<< orphan*/  (* handler ) (TYPE_7__*) ;int /*<<< orphan*/  log; } ;
struct TYPE_16__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  log; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ERROR_ERR ; 
 int /*<<< orphan*/  NGX_HTTP_CHECK_CONNECT_DONE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_6__*) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_event_get_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_check_clean_event (TYPE_4__*) ; 
 scalar_t__ ngx_http_upstream_check_need_exit () ; 
 scalar_t__ ngx_http_upstream_check_peek_one_byte (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_status_update (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 

__attribute__((used)) static void
ngx_http_upstream_check_connect_handler(ngx_event_t *event)
{
    ngx_int_t                            rc;
    ngx_connection_t                    *c;
    ngx_http_upstream_check_peer_t      *peer;
    ngx_http_upstream_check_srv_conf_t  *ucscf;

    if (ngx_http_upstream_check_need_exit()) {
        return;
    }

    peer = event->data;
    ucscf = peer->conf;

    if (peer->pc.connection != NULL) {
        c = peer->pc.connection;
        if ((rc = ngx_http_upstream_check_peek_one_byte(c)) == NGX_OK) {
            goto upstream_check_connect_done;
        } else {
            ngx_close_connection(c);
            peer->pc.connection = NULL;
        }
    }
    ngx_memzero(&peer->pc, sizeof(ngx_peer_connection_t));

    peer->pc.sockaddr = peer->check_peer_addr->sockaddr;
    peer->pc.socklen = peer->check_peer_addr->socklen;
    peer->pc.name = &peer->check_peer_addr->name;

    peer->pc.get = ngx_event_get_peer;
    peer->pc.log = event->log;
    peer->pc.log_error = NGX_ERROR_ERR;

    peer->pc.cached = 0;
    peer->pc.connection = NULL;

    rc = ngx_event_connect_peer(&peer->pc);

    if (rc == NGX_ERROR || rc == NGX_DECLINED) {
        ngx_http_upstream_check_status_update(peer, 0);
        ngx_http_upstream_check_clean_event(peer);
        return;
    }

    /* NGX_OK or NGX_AGAIN */
    c = peer->pc.connection;
    c->data = peer;
    c->log = peer->pc.log;
    c->sendfile = 0;
    c->read->log = c->log;
    c->write->log = c->log;
    c->pool = peer->pool;

upstream_check_connect_done:
    peer->state = NGX_HTTP_CHECK_CONNECT_DONE;

    c->write->handler = peer->send_handler;
    c->read->handler = peer->recv_handler;

    ngx_add_timer(&peer->check_timeout_ev, ucscf->check_timeout);

    /* The kqueue's loop interface needs it. */
    if (rc == NGX_OK) {
        c->write->handler(c->write);
    }
}