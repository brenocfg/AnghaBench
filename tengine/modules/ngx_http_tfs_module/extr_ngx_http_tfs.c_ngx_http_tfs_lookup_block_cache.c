#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ngx_int_t ;
struct TYPE_17__ {int use_cache; } ;
struct TYPE_18__ {size_t segment_index; TYPE_5__* segment_data; } ;
struct TYPE_21__ {int state; int /*<<< orphan*/  log; int /*<<< orphan*/ * tfs_peer_servers; int /*<<< orphan*/  pool; TYPE_14__ block_cache_ctx; int /*<<< orphan*/  name_server_addr; TYPE_1__ file; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_20__ {int /*<<< orphan*/ * ds_addrs; int /*<<< orphan*/  ds_count; } ;
struct TYPE_19__ {int /*<<< orphan*/  block_id; } ;
struct TYPE_22__ {TYPE_3__ block_info; int /*<<< orphan*/  cache_hit; TYPE_2__ segment_info; } ;
typedef  TYPE_5__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_23__ {scalar_t__ ds_addrs; int /*<<< orphan*/  ds_count; } ;
typedef  TYPE_6__ ngx_http_tfs_block_cache_value_t ;
struct TYPE_24__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_7__ ngx_http_tfs_block_cache_key_t ;

/* Variables and functions */
#define  NGX_DECLINED 130 
#define  NGX_ERROR 129 
 size_t NGX_HTTP_TFS_DATA_SERVER ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 int NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
#define  NGX_OK 128 
 int ngx_http_tfs_block_cache_lookup (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_http_tfs_peer_set_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remove_block_cache (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_select_data_server (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_tfs_lookup_block_cache(ngx_http_tfs_t *t)
{
    ngx_int_t                         rc;
    ngx_http_tfs_inet_t              *addr;
    ngx_http_tfs_segment_data_t      *segment_data;
    ngx_http_tfs_block_cache_key_t    key;
    ngx_http_tfs_block_cache_value_t  value;

    segment_data = &t->file.segment_data[t->file.segment_index];
    key.ns_addr = *((uint64_t*)(&t->name_server_addr));
    key.block_id = segment_data->segment_info.block_id;

    rc = ngx_http_tfs_block_cache_lookup(&t->block_cache_ctx, t->pool, t->log,
                                         &key, &value);

    switch (rc) {
    case NGX_DECLINED:
        /* remote cache handler will deal */
        if (t->block_cache_ctx.use_cache & NGX_HTTP_TFS_REMOTE_BLOCK_CACHE) {
            return NGX_DECLINED;
        }
        break;
    case NGX_OK:
        /* local cache hit */
        segment_data->cache_hit = NGX_HTTP_TFS_LOCAL_BLOCK_CACHE;

        segment_data->block_info.ds_count = value.ds_count;
        segment_data->block_info.ds_addrs = (ngx_http_tfs_inet_t *)
                                             value.ds_addrs;

        addr = ngx_http_tfs_select_data_server(t, segment_data);
        if (addr == NULL) {
            ngx_http_tfs_remove_block_cache(t, segment_data);

        } else {
            /* skip GET_BLK_INFO state */
            t->state += 1;
            ngx_http_tfs_peer_set_addr(t->pool,
                          &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER], addr);
        }

       break;
    case NGX_ERROR:
        /* block cache should not affect, go for ns */
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "lookup block cache failed.");
        break;
    }
    rc = NGX_OK;

    ngx_http_tfs_finalize_state(t, rc);

    return rc;
}