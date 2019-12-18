#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int code; } ;
struct TYPE_6__ {TYPE_1__ action; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tfs_peer_servers; int /*<<< orphan*/ * input_filter; void* process_request_body; void* create_request; int /*<<< orphan*/ * retry_handler; int /*<<< orphan*/  state; int /*<<< orphan*/ * tfs_peer; TYPE_2__ r_ctx; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_peer_connection_t ;

/* Variables and functions */
#define  NGX_HTTP_TFS_ACTION_KEEPALIVE 158 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 157 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 156 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 155 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 154 
 size_t NGX_HTTP_TFS_DATA_SERVER ; 
 size_t NGX_HTTP_TFS_NAME_SERVER ; 
 size_t NGX_HTTP_TFS_RC_SERVER ; 
#define  NGX_HTTP_TFS_STATE_READ_DONE 153 
#define  NGX_HTTP_TFS_STATE_READ_GET_BLK_INFO 152 
#define  NGX_HTTP_TFS_STATE_READ_READ_DATA 151 
#define  NGX_HTTP_TFS_STATE_READ_START 150 
#define  NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA 149 
#define  NGX_HTTP_TFS_STATE_REMOVE_DONE 148 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO 147 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT 146 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ 145 
#define  NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT 144 
#define  NGX_HTTP_TFS_STATE_REMOVE_START 143 
#define  NGX_HTTP_TFS_STATE_REMOVE_STAT_FILE 142 
#define  NGX_HTTP_TFS_STATE_STAT_GET_BLK_INFO 141 
#define  NGX_HTTP_TFS_STATE_STAT_START 140 
#define  NGX_HTTP_TFS_STATE_STAT_STAT_FILE 139 
#define  NGX_HTTP_TFS_STATE_WRITE_CLOSE_FILE 138 
#define  NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS 137 
#define  NGX_HTTP_TFS_STATE_WRITE_CREATE_FILE_NAME 136 
#define  NGX_HTTP_TFS_STATE_WRITE_DELETE_DATA 135 
#define  NGX_HTTP_TFS_STATE_WRITE_DONE 134 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO 133 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT 132 
#define  NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ 131 
#define  NGX_HTTP_TFS_STATE_WRITE_START 130 
#define  NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE 129 
#define  NGX_HTTP_TFS_STATE_WRITE_WRITE_DATA 128 
 void* ngx_http_tfs_create_ds_request ; 
 void* ngx_http_tfs_create_ns_request ; 
 void* ngx_http_tfs_create_rcs_request ; 
 void* ngx_http_tfs_process_ds ; 
 void* ngx_http_tfs_process_ds_input_filter ; 
 void* ngx_http_tfs_process_ds_read ; 
 void* ngx_http_tfs_process_ns ; 
 void* ngx_http_tfs_process_rcs ; 
 void* ngx_http_tfs_retry_ds ; 
 void* ngx_http_tfs_retry_ns ; 

__attribute__((used)) static ngx_http_tfs_peer_connection_t *
ngx_http_tfs_select_peer_v1(ngx_http_tfs_t *t)
{
    switch (t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_START:
            t->create_request = ngx_http_tfs_create_rcs_request;
            t->process_request_body = ngx_http_tfs_process_rcs;
            t->input_filter = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_RC_SERVER];

        case NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT:
        case NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ:
        case NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO:
            t->create_request = ngx_http_tfs_create_ns_request;
            t->process_request_body = ngx_http_tfs_process_ns;
            t->input_filter = NULL;
            t->retry_handler = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER];

        case NGX_HTTP_TFS_STATE_REMOVE_STAT_FILE:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ds;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        case NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds_read;
            t->input_filter = ngx_http_tfs_process_ds_input_filter;
            t->retry_handler = ngx_http_tfs_retry_ds;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        case NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds;
            t->input_filter = NULL;
            t->retry_handler = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        case NGX_HTTP_TFS_STATE_REMOVE_DONE:
            return t->tfs_peer;

        default:
            return NULL;
        }
        break;
    case NGX_HTTP_TFS_ACTION_READ_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_READ_START:
            t->create_request = ngx_http_tfs_create_rcs_request;
            t->process_request_body = ngx_http_tfs_process_rcs;
            t->input_filter = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_RC_SERVER];

        case NGX_HTTP_TFS_STATE_READ_GET_BLK_INFO:
            t->create_request = ngx_http_tfs_create_ns_request;
            t->process_request_body = ngx_http_tfs_process_ns;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ns;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER];

        case NGX_HTTP_TFS_STATE_READ_READ_DATA:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds_read;
            t->input_filter = ngx_http_tfs_process_ds_input_filter;
            t->retry_handler = ngx_http_tfs_retry_ds;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        case NGX_HTTP_TFS_STATE_READ_DONE:
            t->input_filter = NULL;
            return t->tfs_peer;

        default:
            return NULL;
        }
        break;
    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_START:
            t->create_request = ngx_http_tfs_create_rcs_request;
            t->process_request_body = ngx_http_tfs_process_rcs;
            t->input_filter = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_RC_SERVER];

        case NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT:
        case NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ:
        case NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS:
        case NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO:
            t->create_request = ngx_http_tfs_create_ns_request;
            t->process_request_body = ngx_http_tfs_process_ns;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ns;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER];

        case NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE:
        case NGX_HTTP_TFS_STATE_WRITE_CREATE_FILE_NAME:
        case NGX_HTTP_TFS_STATE_WRITE_WRITE_DATA:
        case NGX_HTTP_TFS_STATE_WRITE_CLOSE_FILE:
        case NGX_HTTP_TFS_STATE_WRITE_DELETE_DATA:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ds;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        case NGX_HTTP_TFS_STATE_WRITE_DONE:
            t->input_filter = NULL;
            return t->tfs_peer;
        default:
            return NULL;
        }
        break;
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_STAT_START:
            t->create_request = ngx_http_tfs_create_rcs_request;
            t->process_request_body = ngx_http_tfs_process_rcs;
            t->input_filter = NULL;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_RC_SERVER];

        case NGX_HTTP_TFS_STATE_STAT_GET_BLK_INFO:
            t->create_request = ngx_http_tfs_create_ns_request;
            t->process_request_body = ngx_http_tfs_process_ns;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ns;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER];

        case NGX_HTTP_TFS_STATE_STAT_STAT_FILE:
            t->create_request = ngx_http_tfs_create_ds_request;
            t->process_request_body = ngx_http_tfs_process_ds;
            t->input_filter = NULL;
            t->retry_handler = ngx_http_tfs_retry_ds;
            return &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER];

        default:
            return NULL;
        }
        break;

    case NGX_HTTP_TFS_ACTION_KEEPALIVE:
        t->create_request = ngx_http_tfs_create_rcs_request;
        t->process_request_body = ngx_http_tfs_process_rcs;
        t->input_filter = NULL;
        return &t->tfs_peer_servers[NGX_HTTP_TFS_RC_SERVER];

    default:
        break;
    }

    return NULL;
}