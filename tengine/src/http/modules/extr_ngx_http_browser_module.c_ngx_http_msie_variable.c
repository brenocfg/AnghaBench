#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_4__ {scalar_t__ msie; } ;
struct TYPE_5__ {TYPE_1__ headers_in; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_variable_null_value ; 
 int /*<<< orphan*/  ngx_http_variable_true_value ; 

__attribute__((used)) static ngx_int_t
ngx_http_msie_variable(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    if (r->headers_in.msie) {
        *v = ngx_http_variable_true_value;
        return NGX_OK;
    }

    *v = ngx_http_variable_null_value;
    return NGX_OK;
}