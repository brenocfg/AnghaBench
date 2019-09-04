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
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 char* ngx_conf_check_num_bounds (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_linux_rtsig_max ; 

__attribute__((used)) static char *
ngx_check_ngx_overflow_threshold_bounds(ngx_conf_t *cf, void *post, void *data)
{
    if (ngx_linux_rtsig_max) {
        return ngx_conf_check_num_bounds(cf, post, data);
    }

    ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                       "\"rtsig_overflow_threshold\" is not supported "
                       "since Linux 2.6.6-mm2, ignored");

    return NGX_CONF_OK;
}