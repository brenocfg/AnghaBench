#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_10__ {TYPE_2__ value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int not_found; int valid; int len; int /*<<< orphan*/ * data; scalar_t__ no_cacheable; } ;
typedef  TYPE_4__ ngx_http_variable_value_t ;
struct TYPE_8__ {TYPE_3__* te; } ;
struct TYPE_12__ {TYPE_1__ headers_in; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_strlcasestrn (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_internal_trailers_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_table_elt_t  *te;

    te = r->headers_in.te;

    if (te == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    if (ngx_strlcasestrn(te->value.data, te->value.data + te->value.len,
                         (u_char *) "trailers", 8 - 1)
        == NULL)
    {
        v->not_found = 1;
        return NGX_OK;
    }

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    v->data = (u_char *) "trailers";
    v->len = sizeof("trailers") - 1;

    return NGX_OK;
}