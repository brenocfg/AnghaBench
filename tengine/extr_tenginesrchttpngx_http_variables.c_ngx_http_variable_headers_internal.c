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
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {scalar_t__ hash; TYPE_1__ value; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int not_found; int valid; size_t len; int /*<<< orphan*/ * data; scalar_t__ no_cacheable; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_12__ {size_t nelts; TYPE_2__** elts; } ;
typedef  TYPE_5__ ngx_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_headers_internal(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data, u_char sep)
{
    size_t             len;
    u_char            *p, *end;
    ngx_uint_t         i, n;
    ngx_array_t       *a;
    ngx_table_elt_t  **h;

    a = (ngx_array_t *) ((char *) r + data);

    n = a->nelts;
    h = a->elts;

    len = 0;

    for (i = 0; i < n; i++) {

        if (h[i]->hash == 0) {
            continue;
        }

        len += h[i]->value.len + 2;
    }

    if (len == 0) {
        v->not_found = 1;
        return NGX_OK;
    }

    len -= 2;

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    if (n == 1) {
        v->len = (*h)->value.len;
        v->data = (*h)->value.data;

        return NGX_OK;
    }

    p = ngx_pnalloc(r->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    v->len = len;
    v->data = p;

    end = p + len;

    for (i = 0; /* void */ ; i++) {

        if (h[i]->hash == 0) {
            continue;
        }

        p = ngx_copy(p, h[i]->value.data, h[i]->value.len);

        if (p == end) {
            break;
        }

        *p++ = sep; *p++ = ' ';
    }

    return NGX_OK;
}