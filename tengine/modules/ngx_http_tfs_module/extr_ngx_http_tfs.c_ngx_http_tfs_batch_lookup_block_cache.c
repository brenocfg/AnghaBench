#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ngx_int_t ;
struct TYPE_19__ {int use_cache; } ;
struct TYPE_20__ {scalar_t__ segment_count; size_t segment_index; scalar_t__ curr_batch_count; TYPE_7__* segment_data; } ;
struct TYPE_25__ {int /*<<< orphan*/  log; int /*<<< orphan*/  decline_handler; TYPE_12__ block_cache_ctx; TYPE_1__ file; int /*<<< orphan*/  pool; int /*<<< orphan*/  name_server_addr; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
struct TYPE_23__ {int /*<<< orphan*/ * ds_addrs; int /*<<< orphan*/  ds_count; } ;
struct TYPE_21__ {scalar_t__ block_id; } ;
struct TYPE_26__ {int /*<<< orphan*/  cache_hit; TYPE_4__ block_info; TYPE_2__ segment_info; } ;
typedef  TYPE_7__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_27__ {TYPE_5__* value; TYPE_3__* key; } ;
typedef  TYPE_8__ ngx_http_tfs_block_cache_kv_t ;
struct TYPE_28__ {scalar_t__ block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_9__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_18__ {scalar_t__ nelts; TYPE_8__* elts; } ;
typedef  TYPE_10__ ngx_array_t ;
struct TYPE_24__ {scalar_t__ ds_addrs; int /*<<< orphan*/  ds_count; } ;
struct TYPE_22__ {scalar_t__ block_id; } ;

/* Variables and functions */
#define  NGX_DECLINED 130 
#define  NGX_ERROR 129 
 int /*<<< orphan*/  NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 scalar_t__ NGX_HTTP_TFS_MAX_BATCH_COUNT ; 
 int NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
#define  NGX_OK 128 
 int ngx_array_init (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ ngx_array_push (TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_batch_process_start ; 
 int ngx_http_tfs_block_cache_batch_lookup (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_tfs_batch_lookup_block_cache(ngx_http_tfs_t *t)
{
    uint32_t                         i, j, block_count;
    ngx_int_t                        rc;
    ngx_array_t                      keys, kvs;
    ngx_http_tfs_segment_data_t     *segment_data;
    ngx_http_tfs_block_cache_kv_t   *kv;
    ngx_http_tfs_block_cache_key_t  *key;

    block_count = t->file.segment_count - t->file.segment_index;
    if (block_count > NGX_HTTP_TFS_MAX_BATCH_COUNT) {
        block_count = NGX_HTTP_TFS_MAX_BATCH_COUNT;
    }

    rc = ngx_array_init(&keys, t->pool, block_count,
                        sizeof(ngx_http_tfs_block_cache_key_t));
    if (rc == NGX_ERROR) {
        return rc;
    }

    segment_data = &t->file.segment_data[t->file.segment_index];
    for (i = 0; i < block_count; i++) {
        key = (ngx_http_tfs_block_cache_key_t *) ngx_array_push(&keys);
        key->ns_addr = *((uint64_t*)(&t->name_server_addr));
        key->block_id = segment_data[i].segment_info.block_id;
    }

    rc = ngx_array_init(&kvs, t->pool, block_count,
                        sizeof(ngx_http_tfs_block_cache_kv_t));
    if (rc == NGX_ERROR) {
        return rc;
    }

    rc = ngx_http_tfs_block_cache_batch_lookup(&t->block_cache_ctx,
                                               t->pool, t->log,
                                               &keys, &kvs);
    /* local cache hit(maybe partial) */
    if (rc != NGX_ERROR && kvs.nelts > 0) {
        /* local block cache hit count */
        t->file.curr_batch_count += kvs.nelts;
        kv = kvs.elts;
        for (i = 0; i < kvs.nelts; i++, kv++) {
            /* find out segment */
            for (j = 0; j < block_count; j++) {
                if (segment_data[j].segment_info.block_id == kv->key->block_id
                    && segment_data[j].block_info.ds_addrs == NULL)
                {
                    break;
                }
            }

            segment_data[j].block_info.ds_count = kv->value->ds_count;
            segment_data[j].block_info.ds_addrs = (ngx_http_tfs_inet_t *)
                                                   kv->value->ds_addrs;

            segment_data[j].cache_hit = NGX_HTTP_TFS_LOCAL_BLOCK_CACHE;
        }
    }

    switch (rc) {
    case NGX_DECLINED:
        /* remote cache handler will deal */
        if (t->block_cache_ctx.use_cache & NGX_HTTP_TFS_REMOTE_BLOCK_CACHE) {
            return NGX_DECLINED;
        }
        rc = NGX_OK;
        break;
    case NGX_OK:
        /* local cache all hit */
        t->decline_handler = ngx_http_tfs_batch_process_start;
        rc = NGX_DECLINED;
        break;
    case NGX_ERROR:
        /* block cache should not affect, go for ns */
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "batch lookup block cache failed.");
        rc = NGX_OK;
    }

    ngx_http_tfs_finalize_state(t, rc);

    return rc;
}