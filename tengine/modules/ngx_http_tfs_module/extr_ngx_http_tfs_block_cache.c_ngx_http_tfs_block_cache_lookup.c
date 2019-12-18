#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_block_cache_value_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_block_cache_key_t ;
struct TYPE_3__ {int curr_lookup_cache; int use_cache; int /*<<< orphan*/  remote_ctx; int /*<<< orphan*/  local_ctx; } ;
typedef  TYPE_1__ ngx_http_tfs_block_cache_ctx_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 int NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 int NGX_HTTP_TFS_NO_BLOCK_CACHE ; 
 int NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_local_block_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_remote_block_cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_http_tfs_block_cache_lookup(ngx_http_tfs_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log, ngx_http_tfs_block_cache_key_t *key,
    ngx_http_tfs_block_cache_value_t *value)
{
    ngx_int_t  rc = NGX_DECLINED;

    if (ctx->curr_lookup_cache == NGX_HTTP_TFS_LOCAL_BLOCK_CACHE) {

        ctx->curr_lookup_cache = NGX_HTTP_TFS_REMOTE_BLOCK_CACHE;

        if (ctx->use_cache & NGX_HTTP_TFS_LOCAL_BLOCK_CACHE) {
            rc = ngx_http_tfs_local_block_cache_lookup(ctx->local_ctx,
                                                       pool, log, key, value);

            if (rc == NGX_OK) {
                return rc;
            }
        }
    }

    if (ctx->curr_lookup_cache == NGX_HTTP_TFS_REMOTE_BLOCK_CACHE) {

        ctx->curr_lookup_cache = NGX_HTTP_TFS_NO_BLOCK_CACHE;

        if (ctx->use_cache & NGX_HTTP_TFS_REMOTE_BLOCK_CACHE) {
            rc = ngx_http_tfs_remote_block_cache_lookup(&ctx->remote_ctx,
                                                        pool, log, key);
        }
    }

    return rc;
}