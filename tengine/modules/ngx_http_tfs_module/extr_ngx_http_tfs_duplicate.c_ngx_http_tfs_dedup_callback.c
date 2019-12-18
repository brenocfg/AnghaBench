#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_28__ {TYPE_6__* segment_data; int /*<<< orphan*/  cluster_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  use_cache; int /*<<< orphan*/  remote_ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/  cluster_id; } ;
struct TYPE_22__ {int code; } ;
struct TYPE_24__ {TYPE_11__ fsname; int /*<<< orphan*/  file_suffix; int /*<<< orphan*/  unlink_type; TYPE_1__ action; } ;
struct TYPE_29__ {int state; TYPE_7__ file; int /*<<< orphan*/ * out_bufs; void* use_dedup; void* is_stat_dup_file; TYPE_4__ block_cache_ctx; int /*<<< orphan*/  log; int /*<<< orphan*/  data; TYPE_3__ r_ctx; TYPE_2__* tfs_peer; int /*<<< orphan*/  pool; int /*<<< orphan*/  meta_segment_data; TYPE_9__* rc_info_node; } ;
typedef  TYPE_8__ ngx_http_tfs_t ;
struct TYPE_30__ {int /*<<< orphan*/  remote_block_cache_info; int /*<<< orphan*/  use_remote_block_cache; } ;
typedef  TYPE_9__ ngx_http_tfs_rcs_info_t ;
struct TYPE_20__ {int /*<<< orphan*/  dup_file_suffix; int /*<<< orphan*/  dup_file_name; int /*<<< orphan*/  save_body_buffer; int /*<<< orphan*/  file_data; int /*<<< orphan*/  file_ref_count; TYPE_8__* data; } ;
typedef  TYPE_10__ ngx_http_tfs_dedup_ctx_t ;
struct TYPE_26__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_27__ {TYPE_5__ segment_info; } ;
struct TYPE_23__ {int /*<<< orphan*/  body_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 137 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 136 
 void* NGX_HTTP_TFS_NO ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
#define  NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA 135 
#define  NGX_HTTP_TFS_STATE_REMOVE_DONE 134 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO 133 
#define  NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT 132 
#define  NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS 131 
#define  NGX_HTTP_TFS_STATE_WRITE_DONE 130 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO 129 
#define  NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE 128 
 int /*<<< orphan*/  NGX_HTTP_TFS_UNLINK_DELETE ; 
 void* NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_check_filename (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_check_suffix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_remove (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_set (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_get_meta_segment (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_get_remote_block_cache_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_lookup_block_cache (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_tfs_dedup_callback(ngx_http_tfs_dedup_ctx_t *ctx, ngx_int_t rc)
{
    ngx_http_tfs_t           *t;
    ngx_http_tfs_rcs_info_t  *rc_info;

    t = ctx->data;
    rc_info = t->rc_info_node;

    switch (t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT:
            /* exist in tair */
            if (rc == NGX_OK) {
                /* check file name */
                rc = ngx_http_tfs_dedup_check_filename(&ctx->dup_file_name,
                                                       &t->r_ctx.fsname);
                if (rc == NGX_OK) {
                    /* file name match, modify ref count and save tair */
                    if (t->r_ctx.unlink_type == NGX_HTTP_TFS_UNLINK_DELETE) {
                        if (--ctx->file_ref_count <= 0) {
                            /* if ref count is 0,
                             * remove key from tair then unlink file
                             */
                            t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO;
                            t->is_stat_dup_file = NGX_HTTP_TFS_NO;
                            t->tfs_peer->body_buffer = ctx->save_body_buffer;
                            ctx->file_data = t->meta_segment_data;
                            rc = ngx_http_tfs_dedup_remove(ctx, t->pool,
                                                           t->log);
                            /* do not care delete tair fail,
                             * go on unlinking file
                             */
                            if (rc == NGX_ERROR) {
                                ngx_http_tfs_finalize_state(t, NGX_OK);
                            }

                            return;
                        }

                        /* file_ref_count > 0, just save tair */
                        t->state = NGX_HTTP_TFS_STATE_REMOVE_DONE;
                        ctx->file_data = t->meta_segment_data;
                        rc = ngx_http_tfs_dedup_set(ctx, t->pool, t->log);
                        /* do not care save tair fail, return success */
                        if (rc == NGX_ERROR) {
                            ngx_http_tfs_finalize_state(t, NGX_DONE);
                        }

                        return;
                    }
                }

                /* file name not match, unlink file */
                t->tfs_peer->body_buffer = ctx->save_body_buffer;
                t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO;
                t->is_stat_dup_file = NGX_HTTP_TFS_NO;
                ngx_http_tfs_finalize_state(t, NGX_OK);

                return;
            }

            /* not exist in tair, unlink file */
            t->tfs_peer->body_buffer = ctx->save_body_buffer;
            t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO;
            t->is_stat_dup_file = NGX_HTTP_TFS_NO;
            ngx_http_tfs_finalize_state(t, NGX_OK);
            return;
        case NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO:
        case NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA:
            ngx_http_tfs_finalize_state(t, NGX_OK);
            return;
        case NGX_HTTP_TFS_STATE_REMOVE_DONE:
            ngx_http_tfs_finalize_state(t, NGX_DONE);
            return;
        }
        break;
    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS:
        case NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO:
            /* exist in tair */
            if (rc == NGX_OK) {
                /* check suffix */
                rc = ngx_http_tfs_dedup_check_suffix(&ctx->dup_file_name,
                                                     &t->r_ctx.file_suffix);
                if (rc == NGX_OK) {
                    /* suffix match, need to stat file */
                    rc = ngx_http_tfs_raw_fsname_parse(&ctx->dup_file_name,
                                                       &ctx->dup_file_suffix,
                                                       &t->r_ctx.fsname);
                    if (rc == NGX_OK) {
                        t->file.cluster_id = t->r_ctx.fsname.cluster_id;
                        t->is_stat_dup_file = NGX_HTTP_TFS_YES;
                        t->state = NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO;
                    }

                } else {
                    /* suffix not match, need save new tfs file,
                     * do not save tair
                     */
                    t->use_dedup = NGX_HTTP_TFS_NO;
                }
            } /* not exist in tair need save new tfs file and tair */

            /* need reset meta segment */
            rc = ngx_http_tfs_get_meta_segment(t);
            if (rc != NGX_OK) {
                ngx_log_error(NGX_LOG_ERR, t->log, 0,
                              "tfs get meta segment failed");
                ngx_http_tfs_finalize_request(t->data, t,
                                              NGX_HTTP_INTERNAL_SERVER_ERROR);
                return;
            }

            /* lookup block cache */
            if (t->is_stat_dup_file) {
                /* dedup write may need to stat file */
                if (rc_info->use_remote_block_cache) {
                    rc = ngx_http_tfs_get_remote_block_cache_instance(
                              &t->block_cache_ctx.remote_ctx,
                              &rc_info->remote_block_cache_info);
                    if (rc == NGX_ERROR) {
                        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                                     "get remote block cache instance failed.");

                    } else {
                        t->block_cache_ctx.use_cache |=
                            NGX_HTTP_TFS_REMOTE_BLOCK_CACHE;
                    }
                }

                ngx_http_tfs_lookup_block_cache(t);

                return;
            }

            ngx_http_tfs_finalize_state(t, NGX_OK);
            break;
        case NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE:
            if (rc == NGX_OK) {
                t->state = NGX_HTTP_TFS_STATE_WRITE_DONE;
                ngx_http_tfs_finalize_state(t, NGX_DONE);

            } else {
                /* save tair(add ref count) failed,
                 * need save new tfs file, do not save tair
                 */
                t->state = NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS;
                t->is_stat_dup_file = NGX_HTTP_TFS_NO;
                t->use_dedup = NGX_HTTP_TFS_NO;
                /* need reset output buf */
                t->out_bufs = NULL;
                /* need reset block id and file id */
                t->file.segment_data[0].segment_info.block_id = 0;
                t->file.segment_data[0].segment_info.file_id = 0;
                ngx_http_tfs_finalize_state(t, NGX_OK);
            }
            break;
        case NGX_HTTP_TFS_STATE_WRITE_DONE:
            ngx_http_tfs_finalize_state(t, NGX_DONE);
            break;
        }
    }
    return;
}