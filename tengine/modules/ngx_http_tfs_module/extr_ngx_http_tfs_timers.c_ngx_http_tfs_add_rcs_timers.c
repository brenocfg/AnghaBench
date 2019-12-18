#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {TYPE_1__* upstream; } ;
typedef  TYPE_2__ ngx_http_tfs_timers_data_t ;
struct TYPE_11__ {scalar_t__ timer_set; TYPE_5__* data; int /*<<< orphan*/  log; int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_cycle_t ;
struct TYPE_13__ {TYPE_2__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_9__ {int /*<<< orphan*/  rcs_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_timeout_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_tfs_add_rcs_timers(ngx_cycle_t *cycle,
    ngx_http_tfs_timers_data_t *data)
{
    ngx_event_t         *ev;
    ngx_connection_t    *dummy;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, cycle->log, 0,
                   "http check tfs rc servers");

    ev = ngx_pcalloc(cycle->pool, sizeof(ngx_event_t));
    if (ev == NULL) {
        return NGX_ERROR;
    }

    dummy = ngx_pcalloc(cycle->pool, sizeof(ngx_connection_t));
    if (dummy == NULL) {
        return NGX_ERROR;
    }

    dummy->data = data;
    ev->handler = ngx_http_tfs_timeout_handler;
    ev->log = cycle->log;
    ev->data = dummy;
    ev->timer_set = 0;

    ngx_add_timer(ev, data->upstream->rcs_interval);

    return NGX_OK;
}