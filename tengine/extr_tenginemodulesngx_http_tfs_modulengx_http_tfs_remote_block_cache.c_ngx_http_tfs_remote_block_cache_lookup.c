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
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  tair_instance; } ;
typedef  TYPE_1__ ngx_http_tfs_remote_block_cache_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_2__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ ngx_http_tair_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TAIR_INT ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_get_handler ; 
 int /*<<< orphan*/  ngx_http_tfs_tair_get_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_remote_block_cache_lookup(
    ngx_http_tfs_remote_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log, ngx_http_tfs_block_cache_key_t* key)
{
    ngx_int_t             rc;
    ngx_http_tair_data_t  tair_key;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "lookup remote block cache, ns addr: %uL, block id: %uD",
                   key->ns_addr, key->block_id);

    tair_key.type = NGX_HTTP_TAIR_INT;
    tair_key.data = (u_char *)key;
    tair_key.len = NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE;

    rc = ngx_http_tfs_tair_get_helper(
                                    ctx->tair_instance,
                                    pool, log,
                                    &tair_key,
                                    ngx_http_tfs_remote_block_cache_get_handler,
                                    (void *)ctx);

    return rc;
}