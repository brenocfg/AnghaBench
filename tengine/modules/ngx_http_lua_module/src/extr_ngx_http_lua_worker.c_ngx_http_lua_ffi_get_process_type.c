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
struct TYPE_3__ {scalar_t__ master; } ;
typedef  TYPE_1__ ngx_core_conf_t ;
struct TYPE_4__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 scalar_t__ NGX_PROCESS_HELPER ; 
 int NGX_PROCESS_MASTER ; 
 int NGX_PROCESS_PRIVILEGED_AGENT ; 
 scalar_t__ NGX_PROCESS_SINGLE ; 
 int /*<<< orphan*/  ngx_core_module ; 
 TYPE_2__* ngx_cycle ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_is_privileged_agent ; 
 scalar_t__ ngx_process ; 

int
ngx_http_lua_ffi_get_process_type(void)
{
    ngx_core_conf_t  *ccf;

#if defined(HAVE_PRIVILEGED_PROCESS_PATCH) && !NGX_WIN32
    if (ngx_process == NGX_PROCESS_HELPER) {
        if (ngx_is_privileged_agent) {
            return NGX_PROCESS_PRIVILEGED_AGENT;
        }
    }
#endif

    if (ngx_process == NGX_PROCESS_SINGLE) {
        ccf = (ngx_core_conf_t *) ngx_get_conf(ngx_cycle->conf_ctx,
                                               ngx_core_module);

        if (ccf->master) {
            return NGX_PROCESS_MASTER;
        }
    }

    return ngx_process;
}