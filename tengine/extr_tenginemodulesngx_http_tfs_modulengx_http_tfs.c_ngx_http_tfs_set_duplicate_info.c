#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {TYPE_4__* segment_data; } ;
struct TYPE_9__ {scalar_t__ code; } ;
struct TYPE_10__ {TYPE_1__ action; } ;
struct TYPE_14__ {int state; TYPE_5__ file; int /*<<< orphan*/ * out_bufs; void* use_dedup; void* is_stat_dup_file; TYPE_2__ r_ctx; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  dedup_ctx; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
struct TYPE_11__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_12__ {TYPE_3__ segment_info; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 void* NGX_HTTP_TFS_NO ; 
 int NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS ; 
#define  NGX_HTTP_TFS_STATE_WRITE_DONE 129 
#define  NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE 128 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_dedup_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_6__*,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_set_duplicate_info(ngx_http_tfs_t *t)
{
    ngx_int_t  rc;

    rc = ngx_http_tfs_dedup_set(&t->dedup_ctx, t->pool,
                                t->log);
    /* save tair failed */
    if (rc == NGX_ERROR) {
        if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
            switch (t->state) {
            case NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE:
                /* stat success and file status normal */
                /* need save new tfs file, no more dedup */
                t->state = NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS;
                t->is_stat_dup_file = NGX_HTTP_TFS_NO;
                t->use_dedup = NGX_HTTP_TFS_NO;
                /* need reset output buf */
                t->out_bufs = NULL;
                /* need reset block id and file id */
                t->file.segment_data[0].segment_info.block_id = 0;
                t->file.segment_data[0].segment_info.file_id = 0;
                rc = NGX_OK;
                break;
            case NGX_HTTP_TFS_STATE_WRITE_DONE:
                rc = NGX_DONE;
            }
        }

        ngx_http_tfs_finalize_state(t, rc);
    }

    return NGX_OK;
}