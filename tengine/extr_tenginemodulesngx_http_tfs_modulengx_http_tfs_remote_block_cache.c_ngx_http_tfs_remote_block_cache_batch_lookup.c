#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  tair_instance; } ;
typedef  TYPE_2__ ngx_http_tfs_remote_block_cache_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_3__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_1__ key; } ;
typedef  TYPE_4__ ngx_http_tair_key_value_t ;
struct TYPE_15__ {scalar_t__ nelts; TYPE_3__* elts; } ;
typedef  TYPE_5__ ngx_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TAIR_INT ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_5__* ngx_array_create (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ ngx_array_push (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_mget_handler ; 
 int /*<<< orphan*/  ngx_http_tfs_tair_mget_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_remote_block_cache_batch_lookup(
    ngx_http_tfs_remote_block_cache_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t *log, ngx_array_t* keys)
{
    ngx_int_t                        rc;
    ngx_uint_t                       i;
    ngx_array_t                     *tair_kvs;
    ngx_http_tair_key_value_t       *tair_kv;
    ngx_http_tfs_block_cache_key_t  *key;

    tair_kvs = ngx_array_create(pool, keys->nelts,
                                sizeof(ngx_http_tair_key_value_t));
    if (tair_kvs == NULL) {
        return NGX_ERROR;
    }

    key = keys->elts;
    for (i = 0; i < keys->nelts; i++, key++) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                       "batch lookup remote block cache, "
                       "ns addr: %uL, block id: %uD",
                       key->ns_addr, key->block_id);

        tair_kv = (ngx_http_tair_key_value_t *)ngx_array_push(tair_kvs);
        if (tair_kv == NULL) {
            return NGX_ERROR;
        }

        tair_kv->key.type = NGX_HTTP_TAIR_INT;
        tair_kv->key.data = (u_char *)key;
        tair_kv->key.len = NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE;
    }

    rc = ngx_http_tfs_tair_mget_helper(
                                   ctx->tair_instance,
                                   pool, log,
                                   tair_kvs,
                                   ngx_http_tfs_remote_block_cache_mget_handler,
                                   (void *)ctx);
    return rc;
}