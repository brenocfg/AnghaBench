#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ check_keepalive_requests; TYPE_8__* check_type_conf; } ;
typedef  TYPE_5__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_13__ {scalar_t__ timer_set; } ;
struct TYPE_16__ {TYPE_7__* connection; } ;
struct TYPE_19__ {TYPE_4__* shm; int /*<<< orphan*/  (* reinit ) (TYPE_6__*) ;int /*<<< orphan*/ * check_data; int /*<<< orphan*/  state; TYPE_11__ check_timeout_ev; TYPE_3__ pc; int /*<<< orphan*/  index; TYPE_5__* conf; } ;
typedef  TYPE_6__ ngx_http_upstream_check_peer_t ;
struct TYPE_20__ {scalar_t__ error; scalar_t__ requests; TYPE_2__* read; TYPE_1__* write; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_21__ {scalar_t__ need_keepalive; } ;
typedef  TYPE_8__ ngx_check_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  owner; } ;
struct TYPE_15__ {int /*<<< orphan*/  handler; } ;
struct TYPE_14__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_CHECK_ALL_DONE ; 
 int /*<<< orphan*/  NGX_INVALID_PID ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_discard_handler ; 
 int /*<<< orphan*/  ngx_http_upstream_check_dummy_handler ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static void
ngx_http_upstream_check_clean_event(ngx_http_upstream_check_peer_t *peer)
{
    ngx_connection_t                    *c;
    ngx_http_upstream_check_srv_conf_t  *ucscf;
    ngx_check_conf_t                    *cf;

    c = peer->pc.connection;
    ucscf = peer->conf;
    cf = ucscf->check_type_conf;

    if (c) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "http check clean event: index:%i, fd: %d",
                       peer->index, c->fd);
        if (c->error == 0 &&
            cf->need_keepalive &&
            (c->requests < ucscf->check_keepalive_requests))
        {
            c->write->handler = ngx_http_upstream_check_dummy_handler;
            c->read->handler = ngx_http_upstream_check_discard_handler;
        } else {
            ngx_close_connection(c);
            peer->pc.connection = NULL;
        }
    }

    if (peer->check_timeout_ev.timer_set) {
        ngx_del_timer(&peer->check_timeout_ev);
    }

    peer->state = NGX_HTTP_CHECK_ALL_DONE;

    if (peer->check_data != NULL && peer->reinit) {
        peer->reinit(peer);
    }

    peer->shm->owner = NGX_INVALID_PID;
}