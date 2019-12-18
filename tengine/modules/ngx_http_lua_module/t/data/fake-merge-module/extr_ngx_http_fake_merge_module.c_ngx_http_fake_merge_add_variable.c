#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_6__ {scalar_t__ index; TYPE_2__ name; int /*<<< orphan*/  data; int /*<<< orphan*/  get_handler; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ngx_http_variable_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 TYPE_1__* ngx_http_add_variable (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_fake_merge_variables ; 
 scalar_t__ ngx_http_get_variable_index (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t 
ngx_http_fake_merge_add_variable(ngx_conf_t *cf)
{
    ngx_http_variable_t  *var, *v;

    for (v = ngx_http_fake_merge_variables; v->name.len; v++) {
        var = ngx_http_add_variable(cf, &v->name, v->flags);
        if (var == NULL) {
            return NGX_ERROR;
        }
        
        var->get_handler = v->get_handler;
        var->data = v->data;
        v->index = ngx_http_get_variable_index(cf, &v->name);
        if (v->index == (ngx_uint_t) NGX_ERROR) {
            return NGX_ERROR;
        }
    }

    return NGX_OK;

}