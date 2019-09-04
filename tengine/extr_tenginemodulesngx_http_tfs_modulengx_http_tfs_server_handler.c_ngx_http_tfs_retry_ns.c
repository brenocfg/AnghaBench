#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {TYPE_5__* segment_data; } ;
struct TYPE_19__ {int code; } ;
struct TYPE_21__ {int version; int /*<<< orphan*/  is_raw_update; TYPE_1__ action; } ;
struct TYPE_20__ {int /*<<< orphan*/  curr_lookup_cache; } ;
struct TYPE_25__ {scalar_t__ (* decline_handler ) (TYPE_7__*) ;int /*<<< orphan*/  data; TYPE_6__ file; int /*<<< orphan*/  state; void* use_dedup; void* is_stat_dup_file; TYPE_3__ r_ctx; int /*<<< orphan*/  is_process_meta_seg; int /*<<< orphan*/  is_large_file; int /*<<< orphan*/  parent; TYPE_2__ block_cache_ctx; void* retry_curr_ns; int /*<<< orphan*/  name_server_addr; int /*<<< orphan*/ * tfs_peer_servers; int /*<<< orphan*/  pool; int /*<<< orphan*/  name_server_addr_text; int /*<<< orphan*/  rc_info_node; int /*<<< orphan*/  rw_cluster_index; TYPE_8__* tfs_peer; } ;
typedef  TYPE_7__ ngx_http_tfs_t ;
struct TYPE_18__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_26__ {TYPE_10__ peer; } ;
typedef  TYPE_8__ ngx_http_tfs_peer_connection_t ;
struct TYPE_22__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_23__ {TYPE_4__ segment_info; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 130 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 129 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 128 
 scalar_t__ NGX_HTTP_TFS_EXIT_SERVER_OBJECT_NOT_FOUND ; 
 size_t NGX_HTTP_TFS_NAME_SERVER ; 
 void* NGX_HTTP_TFS_NO ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_NO_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_batch_lookup_block_cache (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_connect (TYPE_7__*) ; 
 scalar_t__ ngx_http_tfs_lookup_block_cache (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_peer_set_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_reinit (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_reset_segment_data (TYPE_7__*) ; 
 scalar_t__ ngx_http_tfs_select_name_server (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_7__*) ; 

ngx_int_t
ngx_http_tfs_retry_ns(ngx_http_tfs_t *t)
{
    ngx_int_t                        rc;
    ngx_http_tfs_peer_connection_t  *tp;

    tp = t->tfs_peer;
    tp->peer.free(&tp->peer, tp->peer.data, 0);

    if (!t->retry_curr_ns) {
        t->rw_cluster_index++;
        rc = ngx_http_tfs_select_name_server(t, t->rc_info_node,
                                             &t->name_server_addr,
                                             &t->name_server_addr_text);
        if (rc == NGX_ERROR) {
            return NGX_HTTP_TFS_EXIT_SERVER_OBJECT_NOT_FOUND;
        }

        ngx_http_tfs_peer_set_addr(t->pool,
                                 &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER],
                                 &t->name_server_addr);

        ngx_http_tfs_reset_segment_data(t);

    } else {
        t->retry_curr_ns = NGX_HTTP_TFS_NO;
    }

    switch (t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_READ_FILE:
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
        /* lookup block cache */
        if (t->block_cache_ctx.curr_lookup_cache
            != NGX_HTTP_TFS_NO_BLOCK_CACHE)
        {
            if (!t->parent
                && (t->r_ctx.version == 2
                    || (t->is_large_file && !t->is_process_meta_seg)))
            {
                t->decline_handler = ngx_http_tfs_batch_lookup_block_cache;

            } else {
                t->decline_handler = ngx_http_tfs_lookup_block_cache;
            }
            return t->decline_handler(t);
        }
        break;
    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        /* update not allow retry */
        if (t->r_ctx.is_raw_update) {
            return NGX_ERROR;
        }

        /* stat failed, do not dedup, save new tfs file and do not save tair */
        if (t->is_stat_dup_file) {
            t->is_stat_dup_file = NGX_HTTP_TFS_NO;
            t->use_dedup = NGX_HTTP_TFS_NO;
            t->state = NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS;
            t->file.segment_data[0].segment_info.block_id = 0;
            t->file.segment_data[0].segment_info.file_id = 0;
        }
    }

    if (ngx_http_tfs_reinit(t->data, t) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_http_tfs_connect(t);

    return NGX_OK;
}