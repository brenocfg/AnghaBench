#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {scalar_t__ timer_set; TYPE_3__* data; int /*<<< orphan*/ * log; int /*<<< orphan*/  handler; } ;
struct TYPE_8__ {scalar_t__ timer_set; TYPE_3__* data; int /*<<< orphan*/ * log; int /*<<< orphan*/  handler; } ;
struct TYPE_10__ {TYPE_2__* shm; TYPE_7__ check_ev; int /*<<< orphan*/  reinit; int /*<<< orphan*/  parse; int /*<<< orphan*/  init; int /*<<< orphan*/  recv_handler; int /*<<< orphan*/  send_handler; int /*<<< orphan*/ * pool; TYPE_1__ check_timeout_ev; } ;
typedef  TYPE_3__ ngx_http_upstream_check_peer_t ;
struct TYPE_11__ {int /*<<< orphan*/  reinit; int /*<<< orphan*/  parse; int /*<<< orphan*/  init; int /*<<< orphan*/  recv_handler; int /*<<< orphan*/  send_handler; scalar_t__ need_pool; } ;
typedef  TYPE_4__ ngx_check_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_begin_handler ; 
 int /*<<< orphan*/  ngx_http_upstream_check_timeout_handler ; 
 int /*<<< orphan*/  ngx_pagesize ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_add_timer(ngx_http_upstream_check_peer_t *peer,
    ngx_check_conf_t *check_conf, ngx_msec_t timer, ngx_log_t *log)
{
    peer->check_ev.handler = ngx_http_upstream_check_begin_handler;
    peer->check_ev.log = log;
    peer->check_ev.data = peer;
    peer->check_ev.timer_set = 0;

    peer->check_timeout_ev.handler =
        ngx_http_upstream_check_timeout_handler;
    peer->check_timeout_ev.log = log;
    peer->check_timeout_ev.data = peer;
    peer->check_timeout_ev.timer_set = 0;

    if (check_conf->need_pool) {
        peer->pool = ngx_create_pool(ngx_pagesize, log);
        if (peer->pool == NULL) {
            return NGX_ERROR;
        }
    }

    peer->send_handler = check_conf->send_handler;
    peer->recv_handler = check_conf->recv_handler;

    peer->init = check_conf->init;
    peer->parse = check_conf->parse;
    peer->reinit = check_conf->reinit;

    ngx_add_timer(&peer->check_ev, timer);

    /* TODO: lock */
    peer->shm->ref++;

    return NGX_OK;
}