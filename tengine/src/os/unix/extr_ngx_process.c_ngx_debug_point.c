#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int debug_points; } ;
typedef  TYPE_1__ ngx_core_conf_t ;
struct TYPE_4__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
#define  NGX_DEBUG_POINTS_ABORT 129 
#define  NGX_DEBUG_POINTS_STOP 128 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  ngx_abort () ; 
 int /*<<< orphan*/  ngx_core_module ; 
 TYPE_2__* ngx_cycle ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

void
ngx_debug_point(void)
{
    ngx_core_conf_t  *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(ngx_cycle->conf_ctx,
                                           ngx_core_module);

    switch (ccf->debug_points) {

    case NGX_DEBUG_POINTS_STOP:
        raise(SIGSTOP);
        break;

    case NGX_DEBUG_POINTS_ABORT:
        ngx_abort();
    }
}