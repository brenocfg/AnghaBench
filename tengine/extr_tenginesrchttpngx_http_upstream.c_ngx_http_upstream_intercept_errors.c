#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {scalar_t__ status_n; int /*<<< orphan*/ * www_authenticate; } ;
struct TYPE_19__ {TYPE_3__ headers_in; TYPE_1__* conf; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_18__ {int /*<<< orphan*/ * www_authenticate; int /*<<< orphan*/  headers; } ;
struct TYPE_20__ {TYPE_4__ headers_out; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_21__ {scalar_t__ status; } ;
typedef  TYPE_7__ ngx_http_err_page_t ;
struct TYPE_22__ {TYPE_2__* error_pages; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_16__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_15__ {int /*<<< orphan*/  intercept_errors; scalar_t__ intercept_404; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_NOT_FOUND ; 
 scalar_t__ NGX_HTTP_UNAUTHORIZED ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_6__*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_list_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_intercept_errors(ngx_http_request_t *r,
    ngx_http_upstream_t *u)
{
    ngx_int_t                  status;
    ngx_uint_t                 i;
    ngx_table_elt_t           *h;
    ngx_http_err_page_t       *err_page;
    ngx_http_core_loc_conf_t  *clcf;

    status = u->headers_in.status_n;

    if (status == NGX_HTTP_NOT_FOUND && u->conf->intercept_404) {
        ngx_http_upstream_finalize_request(r, u, NGX_HTTP_NOT_FOUND);
        return NGX_OK;
    }

    if (!u->conf->intercept_errors) {
        return NGX_DECLINED;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (clcf->error_pages == NULL) {
        return NGX_DECLINED;
    }

    err_page = clcf->error_pages->elts;
    for (i = 0; i < clcf->error_pages->nelts; i++) {

        if (err_page[i].status == status) {

            if (status == NGX_HTTP_UNAUTHORIZED
                && u->headers_in.www_authenticate)
            {
                h = ngx_list_push(&r->headers_out.headers);

                if (h == NULL) {
                    ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return NGX_OK;
                }

                *h = *u->headers_in.www_authenticate;

                r->headers_out.www_authenticate = h;
            }

#if (NGX_HTTP_CACHE)

            if (r->cache) {

                if (u->cacheable) {
                    time_t  valid;

                    valid = r->cache->valid_sec;

                    if (valid == 0) {
                        valid = ngx_http_file_cache_valid(u->conf->cache_valid,
                                                          status);
                        if (valid) {
                            r->cache->valid_sec = ngx_time() + valid;
                        }
                    }

                    if (valid) {
                        r->cache->error = status;
                    }
                }

                ngx_http_file_cache_free(r->cache, u->pipe->temp_file);
            }
#endif
            ngx_http_upstream_finalize_request(r, u, status);

            return NGX_OK;
        }
    }

    return NGX_DECLINED;
}