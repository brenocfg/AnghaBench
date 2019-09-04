#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int code; } ;
struct TYPE_10__ {TYPE_1__ action; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; TYPE_2__ r_ctx; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_HTTP_TFS_ACTION_CREATE_DIR 141 
#define  NGX_HTTP_TFS_ACTION_CREATE_FILE 140 
#define  NGX_HTTP_TFS_ACTION_LS_DIR 139 
#define  NGX_HTTP_TFS_ACTION_LS_FILE 138 
#define  NGX_HTTP_TFS_ACTION_MOVE_DIR 137 
#define  NGX_HTTP_TFS_ACTION_MOVE_FILE 136 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 135 
#define  NGX_HTTP_TFS_ACTION_REMOVE_DIR 134 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 133 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 132 
#define  NGX_HTTP_TFS_STATE_REMOVE_GET_FRAG_INFO 131 
#define  NGX_HTTP_TFS_STATE_REMOVE_NOTIFY_MS 130 
#define  NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_MS 129 
#define  NGX_HTTP_TFS_STATE_WRITE_WRITE_MS 128 
 int /*<<< orphan*/  ngx_http_tfs_parse_action_message (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_ls_message (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_read_meta_message (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_write_meta_message (TYPE_3__*) ; 

ngx_int_t
ngx_http_tfs_meta_server_parse_message(ngx_http_tfs_t *t)
{
    uint16_t  action;

    action = t->r_ctx.action.code;

    switch (action) {

    case NGX_HTTP_TFS_ACTION_CREATE_DIR:
    case NGX_HTTP_TFS_ACTION_CREATE_FILE:
    case NGX_HTTP_TFS_ACTION_REMOVE_DIR:
    case NGX_HTTP_TFS_ACTION_MOVE_DIR:
    case NGX_HTTP_TFS_ACTION_MOVE_FILE:
        return ngx_http_tfs_parse_action_message(t);

    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_GET_FRAG_INFO:
            return ngx_http_tfs_parse_read_meta_message(t);
        case NGX_HTTP_TFS_STATE_REMOVE_NOTIFY_MS:
            return ngx_http_tfs_parse_action_message(t);
        default:
            return NGX_ERROR;
        }

    case NGX_HTTP_TFS_ACTION_LS_DIR:
    case NGX_HTTP_TFS_ACTION_LS_FILE:
        return ngx_http_tfs_parse_ls_message(t);

    case NGX_HTTP_TFS_ACTION_READ_FILE:
        return ngx_http_tfs_parse_read_meta_message(t);

    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_MS:
            return ngx_http_tfs_parse_read_meta_message(t);

        case NGX_HTTP_TFS_STATE_WRITE_WRITE_MS:
            return ngx_http_tfs_parse_write_meta_message(t);

        default:
            return NGX_ERROR;
        }
    default:
        return NGX_ERROR;
    }

    return NGX_ERROR;
}