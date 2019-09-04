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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int valid; scalar_t__ not_found; scalar_t__ no_cacheable; int /*<<< orphan*/ * data; int /*<<< orphan*/ * len; } ;
typedef  TYPE_1__ ngx_http_variable_value_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SIZE_T_LEN ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_request_get_size(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    size_t  *sp;

    sp = (size_t *) ((char *) r + data);

    v->data = ngx_pnalloc(r->pool, NGX_SIZE_T_LEN);
    if (v->data == NULL) {
        return NGX_ERROR;
    }

    v->len = ngx_sprintf(v->data, "%uz", *sp) - v->data;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    return NGX_OK;
}