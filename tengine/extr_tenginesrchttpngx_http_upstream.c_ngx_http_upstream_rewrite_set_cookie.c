#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  headers; } ;
struct TYPE_8__ {TYPE_2__* upstream; TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_7__ {scalar_t__ (* rewrite_cookie ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_list_push (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_rewrite_set_cookie(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    ngx_int_t         rc;
    ngx_table_elt_t  *ho;

    ho = ngx_list_push(&r->headers_out.headers);
    if (ho == NULL) {
        return NGX_ERROR;
    }

    *ho = *h;

    if (r->upstream->rewrite_cookie) {
        rc = r->upstream->rewrite_cookie(r, ho);

        if (rc == NGX_DECLINED) {
            return NGX_OK;
        }

#if (NGX_DEBUG)
        if (rc == NGX_OK) {
            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "rewritten cookie: \"%V\"", &ho->value);
        }
#endif

        return rc;
    }

    return NGX_OK;
}