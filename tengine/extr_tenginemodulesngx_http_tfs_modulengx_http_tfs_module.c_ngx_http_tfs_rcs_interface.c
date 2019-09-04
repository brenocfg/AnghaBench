#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  local_addr_text; TYPE_6__ local_addr; } ;
typedef  TYPE_2__ ngx_http_tfs_upstream_t ;
struct TYPE_10__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
struct TYPE_8__ {int nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_http_tfs_get_local_ip (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_tfs_rcs_interface(ngx_conf_t *cf, ngx_http_tfs_upstream_t *tu)
{
    ngx_int_t   rc;
    ngx_str_t  *value;

    if (cf->args->nelts != 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid number of arguments in "
                           "\"rcs_interface\" directive");
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;
    rc = ngx_http_tfs_get_local_ip(value[1], &tu->local_addr);
    if (rc == NGX_ERROR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "device is invalid(%V)",
                           &value[1]);
        return NGX_CONF_ERROR;
    }

    ngx_inet_ntop(AF_INET, &tu->local_addr.sin_addr, tu->local_addr_text,
                  NGX_INET_ADDRSTRLEN);
    return NGX_CONF_OK;
}