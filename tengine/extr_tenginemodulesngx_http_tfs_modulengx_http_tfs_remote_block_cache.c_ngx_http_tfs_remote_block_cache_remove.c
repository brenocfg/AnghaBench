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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  tair_instance; } ;
typedef  TYPE_1__ ngx_http_tfs_remote_block_cache_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_2__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ ngx_http_tair_data_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TAIR_INT ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_tfs_tair_delete_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ngx_http_tfs_remote_block_cache_remove(
    ngx_http_tfs_remote_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log, ngx_http_tfs_block_cache_key_t* key)
{
    ngx_int_t              rc;
    ngx_pool_t            *tmp_pool;
    ngx_array_t            tair_keys;
    ngx_http_tair_data_t  *tair_key;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "remove remote block cache, ns addr: %uL, block id: %uD",
                   key->ns_addr, key->block_id);

    rc = ngx_array_init(&tair_keys, pool, 1, sizeof(ngx_http_tair_data_t));
    if (rc == NGX_ERROR) {
        return;
    }
    tair_key = (ngx_http_tair_data_t*) ngx_array_push(&tair_keys);

    tair_key->type = NGX_HTTP_TAIR_INT;
    tair_key->data = (u_char *)key;
    tair_key->len = NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE;

    /* since we do not care returns,
     * we make a tmp pool and destroy it in callback
     */
    tmp_pool = ngx_create_pool(4096, log);
    if (tmp_pool == NULL) {
        return;
    }

    (void) ngx_http_tfs_tair_delete_helper(
                                  ctx->tair_instance,
                                  tmp_pool, log,
                                  &tair_keys,
                                  ngx_http_tfs_remote_block_cache_dummy_handler,
                                  (void *)tmp_pool);

}