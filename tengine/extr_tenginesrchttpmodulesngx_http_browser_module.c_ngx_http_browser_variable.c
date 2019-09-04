#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ancient_browser_value; int /*<<< orphan*/ * modern_browser_value; } ;
typedef  TYPE_1__ ngx_http_browser_conf_t ;

/* Variables and functions */
 uintptr_t NGX_HTTP_ANCIENT_BROWSER ; 
 uintptr_t NGX_HTTP_MODERN_BROWSER ; 
 int /*<<< orphan*/  NGX_OK ; 
 uintptr_t ngx_http_browser (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_browser_module ; 
 TYPE_1__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_variable_null_value ; 

__attribute__((used)) static ngx_int_t
ngx_http_browser_variable(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    ngx_uint_t                rc;
    ngx_http_browser_conf_t  *cf;

    cf = ngx_http_get_module_loc_conf(r, ngx_http_browser_module);

    rc = ngx_http_browser(r, cf);

    if (data == NGX_HTTP_MODERN_BROWSER && rc == NGX_HTTP_MODERN_BROWSER) {
        *v = *cf->modern_browser_value;
        return NGX_OK;
    }

    if (data == NGX_HTTP_ANCIENT_BROWSER && rc == NGX_HTTP_ANCIENT_BROWSER) {
        *v = *cf->ancient_browser_value;
        return NGX_OK;
    }

    *v = ngx_http_variable_null_value;
    return NGX_OK;
}