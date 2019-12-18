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
 size_t NGX_HTTP_V2_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_v2_chunk_size(ngx_conf_t *cf, void *post, void *data)
{
    size_t *sp = data;

    if (*sp == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "the http2 chunk size cannot be zero");

        return NGX_CONF_ERROR;
    }

    if (*sp > NGX_HTTP_V2_MAX_FRAME_SIZE) {
        *sp = NGX_HTTP_V2_MAX_FRAME_SIZE;
    }

    return NGX_CONF_OK;
}