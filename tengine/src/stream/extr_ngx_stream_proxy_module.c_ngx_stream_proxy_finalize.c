#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_15__ {TYPE_9__* connection; int /*<<< orphan*/ * sockaddr; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_22__ {scalar_t__ start_time; TYPE_10__ peer; TYPE_2__* state; int /*<<< orphan*/  received; TYPE_1__* resolved; } ;
typedef  TYPE_7__ ngx_stream_upstream_t ;
struct TYPE_23__ {TYPE_5__* connection; TYPE_7__* upstream; } ;
typedef  TYPE_8__ ngx_stream_session_t ;
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_24__ {scalar_t__ type; TYPE_6__* ssl; scalar_t__ fd; TYPE_4__* write; TYPE_3__* read; int /*<<< orphan*/  sent; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_21__ {int no_wait_shutdown; } ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;
struct TYPE_19__ {scalar_t__ error; } ;
struct TYPE_18__ {scalar_t__ error; } ;
struct TYPE_17__ {scalar_t__ response_time; int /*<<< orphan*/  bytes_sent; int /*<<< orphan*/  bytes_received; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_PEER_FAILED ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_9__*) ; 
 scalar_t__ ngx_current_msec ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_ssl_shutdown (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_stream_finalize_session (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ngx_stream_proxy_finalize(ngx_stream_session_t *s, ngx_uint_t rc)
{
    ngx_uint_t              state;
    ngx_connection_t       *pc;
    ngx_stream_upstream_t  *u;

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "finalize stream proxy: %i", rc);

    u = s->upstream;

    if (u == NULL) {
        goto noupstream;
    }

    if (u->resolved && u->resolved->ctx) {
        ngx_resolve_name_done(u->resolved->ctx);
        u->resolved->ctx = NULL;
    }

    pc = u->peer.connection;

    if (u->state) {
        if (u->state->response_time == (ngx_msec_t) -1) {
            u->state->response_time = ngx_current_msec - u->start_time;
        }

        if (pc) {
            u->state->bytes_received = u->received;
            u->state->bytes_sent = pc->sent;
        }
    }

    if (u->peer.free && u->peer.sockaddr) {
        state = 0;

        if (pc && pc->type == SOCK_DGRAM
            && (pc->read->error || pc->write->error))
        {
            state = NGX_PEER_FAILED;
        }

        u->peer.free(&u->peer, u->peer.data, state);
        u->peer.sockaddr = NULL;
    }

    if (pc) {
        ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                       "close stream proxy upstream connection: %d", pc->fd);

#if (NGX_STREAM_SSL)
        if (pc->ssl) {
            pc->ssl->no_wait_shutdown = 1;
            (void) ngx_ssl_shutdown(pc);
        }
#endif

        ngx_close_connection(pc);
        u->peer.connection = NULL;
    }

noupstream:

    ngx_stream_finalize_session(s, rc);
}