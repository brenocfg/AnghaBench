#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_30__ {size_t segment_index; scalar_t__ segment_count; int /*<<< orphan*/  curr_batch_count; TYPE_8__* segment_data; } ;
struct TYPE_28__ {int use_cache; int /*<<< orphan*/  local_ctx; } ;
struct TYPE_31__ {int /*<<< orphan*/  log; int /*<<< orphan*/  decline_handler; TYPE_6__ file; int /*<<< orphan*/  pool; int /*<<< orphan*/  name_server_addr_text; TYPE_4__ block_cache_ctx; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ ngx_http_tfs_t ;
struct TYPE_29__ {scalar_t__ block_id; } ;
struct TYPE_27__ {int /*<<< orphan*/ * ds_addrs; scalar_t__ ds_count; } ;
struct TYPE_32__ {TYPE_5__ segment_info; int /*<<< orphan*/  cache_hit; TYPE_3__ block_info; } ;
typedef  TYPE_8__ ngx_http_tfs_segment_data_t ;
struct TYPE_33__ {TYPE_7__* data; } ;
typedef  TYPE_9__ ngx_http_tfs_remote_block_cache_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_21__ {int /*<<< orphan*/ * ds_addrs; scalar_t__ ds_count; } ;
typedef  TYPE_10__ ngx_http_tfs_block_cache_value_t ;
struct TYPE_22__ {scalar_t__ block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_11__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_25__ {int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {scalar_t__ rc; TYPE_2__* value; TYPE_1__ key; } ;
typedef  TYPE_12__ ngx_http_tair_key_value_t ;
struct TYPE_24__ {scalar_t__ nelts; TYPE_12__* elts; } ;
typedef  TYPE_13__ ngx_array_t ;
struct TYPE_26__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 scalar_t__ NGX_HTTP_ETAIR_SUCCESS ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 scalar_t__ NGX_HTTP_TFS_MAX_BATCH_COUNT ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 scalar_t__ NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_batch_process_start ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_local_block_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_remove (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ngx_http_tfs_remote_block_cache_mget_handler(ngx_array_t *kvs, ngx_int_t rc,
    void *data)
{
    u_char                                 *p, *q;
    uint32_t                                ds_count, block_count;
    ngx_uint_t                              i, j, hit_count;
    ngx_http_tfs_t                         *t;
    ngx_http_tair_key_value_t              *kv;
    ngx_http_tfs_segment_data_t            *segment_data;
    ngx_http_tfs_block_cache_key_t          key;
    ngx_http_tfs_block_cache_value_t        value;
    ngx_http_tfs_remote_block_cache_ctx_t  *ctx = data;

    t = ctx->data;

    segment_data = &t->file.segment_data[t->file.segment_index];
    block_count = t->file.segment_count - t->file.segment_index;
    if (block_count > NGX_HTTP_TFS_MAX_BATCH_COUNT) {
        block_count = NGX_HTTP_TFS_MAX_BATCH_COUNT;
    }

    if (rc == NGX_OK) {
        kv = kvs->elts;
        hit_count = 0;
        for (i = 0; i < kvs->nelts; i++, kv++) {
            if (kv->rc != NGX_HTTP_ETAIR_SUCCESS) {
                continue;
            }
            q = kv->key.data;
            p = kv->value->data;
            if (p != NULL
                && (kv->value->len
                    > NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE))
            {
                key.ns_addr = *(uint64_t *)q;
                q += sizeof(uint64_t);
                key.block_id = *(uint32_t *)q;

                ds_count = *(uint32_t *)p;
                p += sizeof(uint32_t);

                if (ds_count > 0) {
                    /* find out segment */
                    for (j = 0; j < block_count; j++) {
                        if(segment_data[j].segment_info.block_id == key.block_id
                           && segment_data[j].block_info.ds_addrs == NULL)
                        {
                            break;
                        }
                    }
                    /* not found, some error happen */
                    if (j == block_count) {
                        continue;
                    }

                    segment_data[j].block_info.ds_count = ds_count;
                    segment_data[j].block_info.ds_addrs = ngx_pcalloc(t->pool,
                                        ds_count * sizeof(ngx_http_tfs_inet_t));
                    if (segment_data[j].block_info.ds_addrs == NULL) {
                        ngx_http_tfs_finalize_request(t->data, t,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
                        return;
                    }
                    ngx_memcpy(segment_data[j].block_info.ds_addrs, p,
                               ds_count * sizeof(ngx_http_tfs_inet_t));

                    if (t->block_cache_ctx.use_cache
                        & NGX_HTTP_TFS_LOCAL_BLOCK_CACHE)
                    {
                        value.ds_count = ds_count;
                        value.ds_addrs =
                            (uint64_t *)segment_data[j].block_info.ds_addrs;
                        ngx_http_tfs_local_block_cache_insert(
                            t->block_cache_ctx.local_ctx, t->log, &key, &value);
                    }

                    hit_count++;
                    segment_data[j].cache_hit = NGX_HTTP_TFS_REMOTE_BLOCK_CACHE;

                    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, t->log, 0,
                                   "remote block cache hit, "
                                   "ns addr: %V, block id: %uD",
                                   &t->name_server_addr_text,
                                   segment_data[j].segment_info.block_id);

                } else {
                    /* remote block cache invalid, need remove it */
                    ngx_http_tfs_remote_block_cache_remove(ctx, t->pool, t->log,
                                                           &key);
                }
            }
        }

        if (hit_count > 0) {
            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                           "batch lookup remote block cache, hit_count: %ui",
                           hit_count);

            /* remote block cache hit count */
            t->file.curr_batch_count += hit_count;

            if (hit_count == kvs->nelts) {
                /* all cache hit, start batch process */
                t->decline_handler = ngx_http_tfs_batch_process_start;
                rc = NGX_DECLINED;
            }
        }

    } else {
        rc = NGX_OK;
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, t->log, 0,
                       "remote block cache miss");
    }

    ngx_http_tfs_finalize_state(t, rc);
}