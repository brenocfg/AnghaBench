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
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {int use_cache; int /*<<< orphan*/  local_ctx; } ;
struct TYPE_25__ {size_t segment_index; TYPE_8__* segment_data; } ;
struct TYPE_31__ {int state; int /*<<< orphan*/  name_server_addr_text; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/ * tfs_peer_servers; TYPE_5__ block_cache_ctx; int /*<<< orphan*/  data; TYPE_1__ file; } ;
typedef  TYPE_7__ ngx_http_tfs_t ;
struct TYPE_30__ {int /*<<< orphan*/  block_id; } ;
struct TYPE_28__ {int ds_count; int /*<<< orphan*/ * ds_addrs; } ;
struct TYPE_32__ {TYPE_6__ segment_info; int /*<<< orphan*/  cache_hit; TYPE_4__ block_info; } ;
typedef  TYPE_8__ ngx_http_tfs_segment_data_t ;
struct TYPE_33__ {TYPE_7__* data; } ;
typedef  TYPE_9__ ngx_http_tfs_remote_block_cache_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_22__ {int ds_count; int /*<<< orphan*/ * ds_addrs; } ;
typedef  TYPE_10__ ngx_http_tfs_block_cache_value_t ;
struct TYPE_23__ {int block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_11__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_26__ {int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {TYPE_3__* value; TYPE_2__ key; } ;
typedef  TYPE_12__ ngx_http_tair_key_value_t ;
struct TYPE_27__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_ETAIR_SUCCESS ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 size_t NGX_HTTP_TFS_DATA_SERVER ; 
 int NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 scalar_t__ NGX_HTTP_TFS_REMOTE_BLOCK_CACHE_VALUE_BASE_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_local_block_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_peer_set_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remote_block_cache_remove (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_select_data_server (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ngx_http_tfs_remote_block_cache_get_handler(ngx_http_tair_key_value_t *kv,
    ngx_int_t rc, void *data)
{
    u_char                                 *p, *q;
    uint32_t                                ds_count;
    ngx_http_tfs_t                         *t;
    ngx_http_tfs_inet_t                    *addr;
    ngx_http_tfs_segment_data_t            *segment_data;
    ngx_http_tfs_block_cache_key_t          key;
    ngx_http_tfs_block_cache_value_t        value;
    ngx_http_tfs_remote_block_cache_ctx_t  *ctx = data;

    t = ctx->data;
    segment_data = &t->file.segment_data[t->file.segment_index];
    if (rc == NGX_HTTP_ETAIR_SUCCESS) {
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
                segment_data->block_info.ds_count = ds_count;
                segment_data->block_info.ds_addrs = ngx_pcalloc(t->pool,
                                       sizeof(ngx_http_tfs_inet_t) * ds_count);
                if (segment_data->block_info.ds_addrs == NULL) {
                    ngx_http_tfs_finalize_request(t->data, t,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return;
                }
                ngx_memcpy(segment_data->block_info.ds_addrs, p,
                           ds_count * sizeof(ngx_http_tfs_inet_t));

                /* insert local block cache */
                if (t->block_cache_ctx.use_cache
                    & NGX_HTTP_TFS_LOCAL_BLOCK_CACHE)
                {
                    value.ds_count = ds_count;
                    value.ds_addrs =
                        (uint64_t *)segment_data->block_info.ds_addrs;
                    ngx_http_tfs_local_block_cache_insert(
                                                   t->block_cache_ctx.local_ctx,
                                                   t->log, &key, &value);
                }

                /* skip GET_BLK_INFO state */
                t->state += 1;

                segment_data->cache_hit = NGX_HTTP_TFS_REMOTE_BLOCK_CACHE;

                /* select data server */
                addr = ngx_http_tfs_select_data_server(t, segment_data);

                ngx_http_tfs_peer_set_addr(t->pool,
                                           &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER],
                                           addr);

            } else {
                /* remote block cache invalid, need remove it */
                ngx_http_tfs_remote_block_cache_remove(ctx, t->pool, t->log,
                                                       &key);
            }
        }

    } else {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, t->log, 0,
                       "lookup remote block cache, "
                       "ns addr: %V, block id: %uD not found",
                       &t->name_server_addr_text,
                       segment_data->segment_info.block_id);
    }

    ngx_http_tfs_finalize_state(t, NGX_OK);
}