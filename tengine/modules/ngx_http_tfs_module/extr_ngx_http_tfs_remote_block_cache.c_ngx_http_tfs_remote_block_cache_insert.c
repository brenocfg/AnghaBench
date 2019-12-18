#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  tair_instance; } ;
typedef  TYPE_1__ ngx_http_tfs_remote_block_cache_ctx_t ;
struct TYPE_11__ {int ds_count; int /*<<< orphan*/  ds_addrs; } ;
typedef  TYPE_2__ ngx_http_tfs_block_cache_value_t ;
struct TYPE_12__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_3__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_13__ {int len; void* type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ ngx_http_tair_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 void* NGX_HTTP_TAIR_INT ; 
 int NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE ; 
 int NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_tfs_tair_put_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ *,int) ; 

ngx_int_t
ngx_http_tfs_remote_block_cache_insert(
    ngx_http_tfs_remote_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log,
    ngx_http_tfs_block_cache_key_t *key,
    ngx_http_tfs_block_cache_value_t *value)
{
    ngx_int_t             rc;
    ngx_pool_t           *tmp_pool;
    ngx_http_tair_data_t  tair_key, tair_value;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "insert remote block cache, "
                   "ns addr: %uL, block id: %uD",
                   key->ns_addr, key->block_id);

    tair_key.type = NGX_HTTP_TAIR_INT;
    tair_key.data = (u_char *)key;
    tair_key.len = NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE;

    tair_value.len = NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE
                      + value->ds_count * sizeof(uint64_t);
    tair_value.data = ngx_pcalloc(pool, tair_value.len);
    if (tair_value.data == NULL) {
        return NGX_ERROR;
    }
    *(uint32_t*)tair_value.data = value->ds_count;
    ngx_memcpy(tair_value.data+ NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE,
               value->ds_addrs, value->ds_count * sizeof(uint64_t));
    tair_value.type = NGX_HTTP_TAIR_INT;

    /* since we do not care returns,
     * we make a tmp pool and destroy it in callback
     */
    tmp_pool = ngx_create_pool(4096, log);
    if (tmp_pool == NULL) {
        return NGX_ERROR;
    }

    rc = ngx_http_tfs_tair_put_helper(
                                  ctx->tair_instance,
                                  tmp_pool, log,
                                  &tair_key, &tair_value,
                                  0/*expire*/, 0/* do not care version */,
                                  ngx_http_tfs_remote_block_cache_dummy_handler,
                                  (void *)tmp_pool);

    return rc;
}