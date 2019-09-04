#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
struct TYPE_14__ {scalar_t__ len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  headers_in; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_16__ {int offset; int /*<<< orphan*/  no_override; } ;
typedef  TYPE_3__ ngx_http_lua_header_val_t ;
struct TYPE_17__ {scalar_t__ nelts; scalar_t__ nalloc; } ;
typedef  TYPE_4__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 int /*<<< orphan*/  ngx_array_destroy (TYPE_4__*) ; 
 scalar_t__ ngx_array_init (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** ngx_array_push (TYPE_4__*) ; 
 scalar_t__ ngx_http_set_header_helper (TYPE_2__*,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_builtin_multi_header(ngx_http_request_t *r,
    ngx_http_lua_header_val_t *hv, ngx_str_t *value)
{
    ngx_array_t       *headers;
    ngx_table_elt_t  **v, *h;

    headers = (ngx_array_t *) ((char *) &r->headers_in + hv->offset);

    if (!hv->no_override && headers->nelts > 0) {
        ngx_array_destroy(headers);

        if (ngx_array_init(headers, r->pool, 2,
                           sizeof(ngx_table_elt_t *))
            != NGX_OK)
        {
            return NGX_ERROR;
        }

        dd("clear multi-value headers: %d", (int) headers->nelts);
    }

#if 1
    if (headers->nalloc == 0) {
        if (ngx_array_init(headers, r->pool, 2,
                           sizeof(ngx_table_elt_t *))
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }
#endif

    if (ngx_http_set_header_helper(r, hv, value, &h) == NGX_ERROR) {
        return NGX_ERROR;
    }

    if (value->len == 0) {
        return NGX_OK;
    }

    dd("new multi-value header: %p", h);

    v = ngx_array_push(headers);
    if (v == NULL) {
        return NGX_ERROR;
    }

    *v = h;
    return NGX_OK;
}