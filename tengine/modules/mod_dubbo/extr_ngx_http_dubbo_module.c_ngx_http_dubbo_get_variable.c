#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {scalar_t__ valid; int /*<<< orphan*/  len; int /*<<< orphan*/ * data; scalar_t__ not_found; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_hash_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_variable (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_dubbo_get_variable(ngx_http_request_t *r, ngx_str_t *name, ngx_str_t *value)
{
    u_char                      *low;
    ngx_str_t                    var;
    ngx_uint_t                   hash;
    ngx_http_variable_value_t   *vv;

    if (0 >= name->len || NULL == name->data) {
        return NGX_ERROR;
    }

    low = ngx_pnalloc(r->pool, name->len);
    if (low == NULL) {
        return NGX_ERROR;
    }

    hash = ngx_hash_strlow(low, name->data, name->len);
    var.data = low;
    var.len = name->len;

    vv = ngx_http_get_variable(r, &var, hash);

    if (vv == NULL || vv->not_found || vv->valid == 0) {
        return NGX_ERROR;
    }

    value->data = vv->data;
    value->len = vv->len;

    return NGX_OK;
}