#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_10__ {int /*<<< orphan*/  busy_bufs; int /*<<< orphan*/  free_bufs; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  ngx_buf_tag_t ;
struct TYPE_8__ {TYPE_2__* data; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_output_filter (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_output_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t            rc;
    ngx_http_lua_ctx_t  *ctx;
    ngx_http_request_t  *ar; /* active request */

    ar = r->connection->data;

    if (ar != r) {

        /* bypass ngx_http_postpone_filter_module */

        r->connection->data = r;
        rc = ngx_http_output_filter(r, in);
        r->connection->data = ar;
        return rc;
    }

    rc = ngx_http_output_filter(r, in);

    if (rc == NGX_ERROR) {
        return NGX_ERROR;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

#if nginx_version >= 1001004
    ngx_chain_update_chains(r->pool,
#else
    ngx_chain_update_chains(
#endif
                            &ctx->free_bufs, &ctx->busy_bufs, &in,
                            (ngx_buf_tag_t) &ngx_http_lua_module);

    return rc;
}