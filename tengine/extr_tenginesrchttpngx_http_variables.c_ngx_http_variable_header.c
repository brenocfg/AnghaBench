#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_1__ value; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int valid; int not_found; int /*<<< orphan*/  data; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_header(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    ngx_table_elt_t  *h;

    h = *(ngx_table_elt_t **) ((char *) r + data);

    if (h) {
        v->len = h->value.len;
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->data = h->value.data;

    } else {
        v->not_found = 1;
    }

    return NGX_OK;
}