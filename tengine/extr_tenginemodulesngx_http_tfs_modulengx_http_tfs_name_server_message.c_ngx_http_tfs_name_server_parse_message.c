#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int code; } ;
struct TYPE_11__ {int version; TYPE_1__ action; } ;
struct TYPE_10__ {size_t segment_index; int /*<<< orphan*/ * segment_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  state; int /*<<< orphan*/  is_process_meta_seg; int /*<<< orphan*/  is_large_file; TYPE_3__ r_ctx; int /*<<< orphan*/  is_rolling_back; int /*<<< orphan*/  parent; TYPE_2__ file; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_segment_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 138 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 137 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 136 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 135 
 int /*<<< orphan*/  NGX_HTTP_TFS_CMD_GET_CLUSTER_ID_NS ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_CMD_GET_GROUP_COUNT ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_CMD_GET_GROUP_SEQ ; 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO 134 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT 133 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ 132 
#define  NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS 131 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO 130 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT 129 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ 128 
 int /*<<< orphan*/  ngx_http_tfs_parse_batch_block_info_message (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_block_info_message (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_ctl_message (TYPE_4__*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_name_server_parse_message(ngx_http_tfs_t *t)
{
    uint16_t                      action;
    ngx_int_t                     rc;
    ngx_http_tfs_segment_data_t  *segment_data;

    rc = NGX_ERROR;
    action = t->r_ctx.action.code;
    segment_data = &t->file.segment_data[t->file.segment_index];

    switch (action) {
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
        return ngx_http_tfs_parse_block_info_message(t, segment_data);

    case NGX_HTTP_TFS_ACTION_READ_FILE:
        if (!t->parent
            && (t->r_ctx.version == 2
                || (t->is_large_file && !t->is_process_meta_seg)))
        {
            rc = ngx_http_tfs_parse_batch_block_info_message(t, segment_data);

        } else {
            rc = ngx_http_tfs_parse_block_info_message(t, segment_data);
        }
        return rc;

    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT:
            return ngx_http_tfs_parse_ctl_message(t,
                NGX_HTTP_TFS_CMD_GET_GROUP_COUNT);

        case NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ:
            return ngx_http_tfs_parse_ctl_message(t,
                NGX_HTTP_TFS_CMD_GET_GROUP_SEQ);

        case NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS:
            return ngx_http_tfs_parse_ctl_message(t,
                NGX_HTTP_TFS_CMD_GET_CLUSTER_ID_NS);

        case NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO:
            if (!t->parent
                && !t->is_rolling_back
                && (t->r_ctx.version == 2
                    || (t->is_large_file && !t->is_process_meta_seg)))
            {
                rc = ngx_http_tfs_parse_batch_block_info_message(t,
                                                                 segment_data);

            } else {
                rc = ngx_http_tfs_parse_block_info_message(t, segment_data);
            }
        }
        return rc;

    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT:
            rc = ngx_http_tfs_parse_ctl_message(t,
                                              NGX_HTTP_TFS_CMD_GET_GROUP_COUNT);
            return rc;

        case NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ:
            rc = ngx_http_tfs_parse_ctl_message(t,
                                                NGX_HTTP_TFS_CMD_GET_GROUP_SEQ);
            return rc;

        case NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO:
            return ngx_http_tfs_parse_block_info_message(t, segment_data);

        default:
            break;
        }
    }

    return NGX_ERROR;
}