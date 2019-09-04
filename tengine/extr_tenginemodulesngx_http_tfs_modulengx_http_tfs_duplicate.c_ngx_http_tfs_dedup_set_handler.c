#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_dedup_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_ETAIR_SUCCESS ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_tfs_dedup_set_handler(ngx_int_t rc, void *data)
{
    ngx_http_tfs_dedup_ctx_t  *ctx;

    ctx = data;

    if (rc == NGX_HTTP_ETAIR_SUCCESS) {
        rc = NGX_OK;

    } else {
        rc = NGX_ERROR;
    }
    ngx_http_tfs_dedup_callback(ctx, rc);
}