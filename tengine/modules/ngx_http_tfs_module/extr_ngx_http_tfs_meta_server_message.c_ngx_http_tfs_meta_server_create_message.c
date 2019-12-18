#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_17__ {int /*<<< orphan*/  len; } ;
struct TYPE_13__ {int code; } ;
struct TYPE_15__ {TYPE_5__ file_path_s; TYPE_1__ action; } ;
struct TYPE_14__ {int /*<<< orphan*/  left_length; int /*<<< orphan*/  file_offset; } ;
struct TYPE_16__ {int /*<<< orphan*/ * json_output; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; TYPE_3__ r_ctx; TYPE_2__ file; int /*<<< orphan*/  state; TYPE_5__ last_file_path; int /*<<< orphan*/  last_dir_level; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
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
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 int /*<<< orphan*/ * ngx_http_tfs_create_action_message (TYPE_4__*,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_create_ls_message (TYPE_4__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_create_read_meta_message (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_tfs_create_write_meta_message (TYPE_4__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_json_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

ngx_chain_t *
ngx_http_tfs_meta_server_create_message(ngx_http_tfs_t *t)
{
    uint16_t      msg_type;
    ngx_chain_t  *cl;

    cl = NULL;
    msg_type = t->r_ctx.action.code;

    switch (msg_type) {

    case NGX_HTTP_TFS_ACTION_CREATE_DIR:
    case NGX_HTTP_TFS_ACTION_CREATE_FILE:
        ngx_log_error(NGX_LOG_DEBUG, t->log, 0,
                      "will create path: "
                      "last_dir_level: %i, dir_len: %i, last_file_path: %V",
                      t->last_dir_level,
                      t->last_file_path.len,
                      &t->last_file_path);
        cl = ngx_http_tfs_create_action_message(t, &t->last_file_path, NULL);
        break;

    case NGX_HTTP_TFS_ACTION_MOVE_DIR:
    case NGX_HTTP_TFS_ACTION_MOVE_FILE:
        cl = ngx_http_tfs_create_action_message(t, &t->r_ctx.file_path_s,
                                                &t->last_file_path);
        break;

    case NGX_HTTP_TFS_ACTION_REMOVE_DIR:
        cl = ngx_http_tfs_create_action_message(t, &t->r_ctx.file_path_s, NULL);
        break;

    case NGX_HTTP_TFS_ACTION_READ_FILE:
        cl = ngx_http_tfs_create_read_meta_message(t, t->file.file_offset,
                                                   t->file.left_length);
        break;

    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_MS:
            cl = ngx_http_tfs_create_read_meta_message(t, 0, 0);
            break;
        case NGX_HTTP_TFS_STATE_WRITE_WRITE_MS:
            cl = ngx_http_tfs_create_write_meta_message(t);
            break;
        }
        break;

    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch (t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_GET_FRAG_INFO:
            cl = ngx_http_tfs_create_read_meta_message(t, t->file.file_offset,
                                                       t->file.left_length);
            break;
        case NGX_HTTP_TFS_STATE_REMOVE_NOTIFY_MS:
            cl = ngx_http_tfs_create_action_message(t, &t->r_ctx.file_path_s,
                                                    NULL);
            break;
        }
        break;

    case NGX_HTTP_TFS_ACTION_LS_DIR:
    case NGX_HTTP_TFS_ACTION_LS_FILE:
        t->json_output = ngx_http_tfs_json_init(t->log, t->pool);
        if (t->json_output == NULL) {
            return NULL;
        }
        cl = ngx_http_tfs_create_ls_message(t);
        break;
    }

    return cl;
}