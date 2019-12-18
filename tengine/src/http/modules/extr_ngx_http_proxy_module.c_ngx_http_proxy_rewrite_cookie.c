#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ value; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {scalar_t__ cookie_paths; scalar_t__ cookie_domains; } ;
typedef  TYPE_3__ ngx_http_proxy_loc_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 TYPE_3__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 scalar_t__ ngx_http_proxy_rewrite_cookie_value (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_strcasestrn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ngx_strchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_rewrite_cookie(ngx_http_request_t *r, ngx_table_elt_t *h)
{
    size_t                      prefix;
    u_char                     *p;
    ngx_int_t                   rc, rv;
    ngx_http_proxy_loc_conf_t  *plcf;

    p = (u_char *) ngx_strchr(h->value.data, ';');
    if (p == NULL) {
        return NGX_DECLINED;
    }

    prefix = p + 1 - h->value.data;

    rv = NGX_DECLINED;

    plcf = ngx_http_get_module_loc_conf(r, ngx_http_proxy_module);

    if (plcf->cookie_domains) {
        p = ngx_strcasestrn(h->value.data + prefix, "domain=", 7 - 1);

        if (p) {
            rc = ngx_http_proxy_rewrite_cookie_value(r, h, p + 7,
                                                     plcf->cookie_domains);
            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }

            if (rc != NGX_DECLINED) {
                rv = rc;
            }
        }
    }

    if (plcf->cookie_paths) {
        p = ngx_strcasestrn(h->value.data + prefix, "path=", 5 - 1);

        if (p) {
            rc = ngx_http_proxy_rewrite_cookie_value(r, h, p + 5,
                                                     plcf->cookie_paths);
            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }

            if (rc != NGX_DECLINED) {
                rv = rc;
            }
        }
    }

    return rv;
}