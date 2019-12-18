#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_5__* connection; int /*<<< orphan*/  name; } ;
struct TYPE_23__ {void* start_time; TYPE_15__ peer; TYPE_12__* state; int /*<<< orphan*/  proxy_protocol; scalar_t__ connected; } ;
typedef  TYPE_2__ ngx_stream_upstream_t ;
typedef  int /*<<< orphan*/  ngx_stream_upstream_state_t ;
struct TYPE_24__ {int /*<<< orphan*/  upstream_states; TYPE_2__* upstream; TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
struct TYPE_25__ {int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  proxy_protocol; } ;
typedef  TYPE_4__ ngx_stream_proxy_srv_conf_t ;
typedef  void* ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {TYPE_17__* write; TYPE_1__* read; TYPE_13__* log; int /*<<< orphan*/  pool; TYPE_3__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_22__ {void* handler; TYPE_13__* log; } ;
struct TYPE_21__ {void* handler; TYPE_13__* log; } ;
struct TYPE_19__ {char* action; } ;
struct TYPE_18__ {int /*<<< orphan*/  peer; void* response_time; void* first_byte_time; void* connect_time; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_STREAM_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_17__*,int /*<<< orphan*/ ) ; 
 TYPE_12__* ngx_array_push (int /*<<< orphan*/ ) ; 
 void* ngx_current_msec ; 
 scalar_t__ ngx_event_connect_peer (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_12__*,int) ; 
 TYPE_4__* ngx_stream_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* ngx_stream_proxy_connect_handler ; 
 int /*<<< orphan*/  ngx_stream_proxy_finalize (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_proxy_init_upstream (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_stream_proxy_module ; 
 int /*<<< orphan*/  ngx_stream_proxy_next_upstream (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_stream_proxy_connect(ngx_stream_session_t *s)
{
    ngx_int_t                     rc;
    ngx_connection_t             *c, *pc;
    ngx_stream_upstream_t        *u;
    ngx_stream_proxy_srv_conf_t  *pscf;

    c = s->connection;

    c->log->action = "connecting to upstream";

    pscf = ngx_stream_get_module_srv_conf(s, ngx_stream_proxy_module);

    u = s->upstream;

    u->connected = 0;
    u->proxy_protocol = pscf->proxy_protocol;

    if (u->state) {
        u->state->response_time = ngx_current_msec - u->start_time;
    }

    u->state = ngx_array_push(s->upstream_states);
    if (u->state == NULL) {
        ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_memzero(u->state, sizeof(ngx_stream_upstream_state_t));

    u->start_time = ngx_current_msec;

    u->state->connect_time = (ngx_msec_t) -1;
    u->state->first_byte_time = (ngx_msec_t) -1;
    u->state->response_time = (ngx_msec_t) -1;

    rc = ngx_event_connect_peer(&u->peer);

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, c->log, 0, "proxy connect: %i", rc);

    if (rc == NGX_ERROR) {
        ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return;
    }

    u->state->peer = u->peer.name;

    if (rc == NGX_BUSY) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0, "no live upstreams");
        ngx_stream_proxy_finalize(s, NGX_STREAM_BAD_GATEWAY);
        return;
    }

    if (rc == NGX_DECLINED) {
        ngx_stream_proxy_next_upstream(s);
        return;
    }

    /* rc == NGX_OK || rc == NGX_AGAIN || rc == NGX_DONE */

    pc = u->peer.connection;

    pc->data = s;
    pc->log = c->log;
    pc->pool = c->pool;
    pc->read->log = c->log;
    pc->write->log = c->log;

    if (rc != NGX_AGAIN) {
        ngx_stream_proxy_init_upstream(s);
        return;
    }

    pc->read->handler = ngx_stream_proxy_connect_handler;
    pc->write->handler = ngx_stream_proxy_connect_handler;

    ngx_add_timer(pc->write, pscf->connect_timeout);
}