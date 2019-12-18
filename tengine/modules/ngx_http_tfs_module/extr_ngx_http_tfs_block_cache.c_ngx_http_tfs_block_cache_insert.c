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
typedef  int /*<<< orphan*/  ngx_http_tfs_block_cache_value_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_block_cache_key_t ;
struct TYPE_3__ {int use_cache; int /*<<< orphan*/  local_ctx; int /*<<< orphan*/  remote_ctx; } ;
typedef  TYPE_1__ ngx_http_tfs_block_cache_ctx_t ;

/* Variables and functions */
 int NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 int NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 int /*<<< orphan*/  ngx_http_tfs_local_block_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ngx_http_tfs_block_cache_insert(ngx_http_tfs_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log, ngx_http_tfs_block_cache_key_t *key,
    ngx_http_tfs_block_cache_value_t *value)
{
    if (ctx->use_cache & NGX_HTTP_TFS_REMOTE_BLOCK_CACHE) {
        ngx_http_tfs_remote_block_cache_insert(&ctx->remote_ctx,
                                               pool, log, key, value);
    }

    if (ctx->use_cache & NGX_HTTP_TFS_LOCAL_BLOCK_CACHE) {
        ngx_http_tfs_local_block_cache_insert(ctx->local_ctx, log, key, value);
    }
}