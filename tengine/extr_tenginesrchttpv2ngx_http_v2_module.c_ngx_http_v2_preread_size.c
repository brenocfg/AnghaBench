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
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static char *
ngx_http_v2_preread_size(ngx_conf_t *cf, void *post, void *data)
{
    size_t *sp = data;

    if (*sp > NGX_HTTP_V2_MAX_WINDOW) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "the maximum body preread buffer size is %uz",
                           NGX_HTTP_V2_MAX_WINDOW);

        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}