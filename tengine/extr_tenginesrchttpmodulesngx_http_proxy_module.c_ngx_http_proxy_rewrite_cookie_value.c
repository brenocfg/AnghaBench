#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_1__ value; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_11__ {scalar_t__ (* handler ) (int /*<<< orphan*/ *,TYPE_2__*,size_t,size_t,TYPE_3__*) ;} ;
typedef  TYPE_3__ ngx_http_proxy_rewrite_t ;
struct TYPE_12__ {size_t nelts; TYPE_3__* elts; } ;
typedef  TYPE_4__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ ngx_strchr (int /*<<< orphan*/ *,char) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_2__*,size_t,size_t,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_rewrite_cookie_value(ngx_http_request_t *r, ngx_table_elt_t *h,
    u_char *value, ngx_array_t *rewrites)
{
    size_t                     len, prefix;
    u_char                    *p;
    ngx_int_t                  rc;
    ngx_uint_t                 i;
    ngx_http_proxy_rewrite_t  *pr;

    prefix = value - h->value.data;

    p = (u_char *) ngx_strchr(value, ';');

    len = p ? (size_t) (p - value) : (h->value.len - prefix);

    pr = rewrites->elts;

    for (i = 0; i < rewrites->nelts; i++) {
        rc = pr[i].handler(r, h, prefix, len, &pr[i]);

        if (rc != NGX_DECLINED) {
            return rc;
        }
    }

    return NGX_DECLINED;
}