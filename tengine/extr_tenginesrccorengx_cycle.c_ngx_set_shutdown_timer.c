#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_7__ {scalar_t__ shutdown_timeout; } ;
typedef  TYPE_2__ ngx_core_conf_t ;
struct TYPE_8__ {int cancelable; int /*<<< orphan*/  log; TYPE_1__* data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_add_timer (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ngx_shutdown_event ; 
 int /*<<< orphan*/  ngx_shutdown_timer_handler ; 

void
ngx_set_shutdown_timer(ngx_cycle_t *cycle)
{
    ngx_core_conf_t  *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    if (ccf->shutdown_timeout) {
        ngx_shutdown_event.handler = ngx_shutdown_timer_handler;
        ngx_shutdown_event.data = cycle;
        ngx_shutdown_event.log = cycle->log;
        ngx_shutdown_event.cancelable = 1;

        ngx_add_timer(&ngx_shutdown_event, ccf->shutdown_timeout);
    }
}