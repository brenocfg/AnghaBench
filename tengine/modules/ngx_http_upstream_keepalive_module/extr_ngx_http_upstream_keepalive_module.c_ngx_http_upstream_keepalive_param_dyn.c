#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {scalar_t__ slice_var_index; } ;
typedef  TYPE_2__ ngx_http_upstream_keepalive_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_get_variable_index (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_keepalive_param_dyn(ngx_conf_t *cf, void *conf,
    ngx_str_t *val)
{
    ngx_http_upstream_keepalive_srv_conf_t  *kcf = conf;

    if (val->data[0] == '$') {
        val->data++;
        val->len--;
    }

    kcf->slice_var_index = ngx_http_get_variable_index(cf, val);

    return kcf->slice_var_index == NGX_ERROR ? NGX_ERROR : NGX_OK;
}