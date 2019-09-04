#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_init_error_signals (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_backtrace_init_worker(ngx_cycle_t *cycle)
{
    if (ngx_init_error_signals(cycle->log) == NGX_ERROR) {
        return NGX_ERROR;
    }

    return NGX_OK;
}