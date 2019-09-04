#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int NGX_ERROR ; 

int
ngx_http_lua_ffi_enable_privileged_agent(char **err)
{
#ifdef HAVE_PRIVILEGED_PROCESS_PATCH
    ngx_core_conf_t   *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(ngx_cycle->conf_ctx,
                                           ngx_core_module);

    ccf->privileged_agent = 1;

    return NGX_OK;

#else
    *err = "missing privileged agent process patch in the nginx core";
    return NGX_ERROR;
#endif
}