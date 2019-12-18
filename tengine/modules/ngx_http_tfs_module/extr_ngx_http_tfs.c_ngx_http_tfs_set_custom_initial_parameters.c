#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int code; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  file_type; int /*<<< orphan*/  file_path_s; int /*<<< orphan*/  file_path_d; TYPE_1__ action; int /*<<< orphan*/  file_suffix; } ;
struct TYPE_7__ {int /*<<< orphan*/  left_length; int /*<<< orphan*/  file_offset; } ;
struct TYPE_9__ {int last_file_pid; TYPE_3__ r_ctx; TYPE_2__ file; int /*<<< orphan*/  last_file_type; int /*<<< orphan*/  last_file_path; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;

/* Variables and functions */
#define  NGX_HTTP_TFS_ACTION_CREATE_DIR 135 
#define  NGX_HTTP_TFS_ACTION_CREATE_FILE 134 
#define  NGX_HTTP_TFS_ACTION_LS_DIR 133 
#define  NGX_HTTP_TFS_ACTION_LS_FILE 132 
#define  NGX_HTTP_TFS_ACTION_MOVE_DIR 131 
#define  NGX_HTTP_TFS_ACTION_MOVE_FILE 130 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 129 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 128 

void
ngx_http_tfs_set_custom_initial_parameters(ngx_http_tfs_t *t)
{
    /* for stat log */
    t->file_name = t->r_ctx.file_path_s;
    t->r_ctx.file_suffix = t->r_ctx.file_path_d;

    switch(t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_CREATE_DIR:
    case NGX_HTTP_TFS_ACTION_CREATE_FILE:
        t->last_file_path = t->r_ctx.file_path_s;
        break;

    case NGX_HTTP_TFS_ACTION_MOVE_DIR:
    case NGX_HTTP_TFS_ACTION_MOVE_FILE:
        t->last_file_path = t->r_ctx.file_path_d;
        break;

    case NGX_HTTP_TFS_ACTION_LS_DIR:
    case NGX_HTTP_TFS_ACTION_LS_FILE:
        /* set initial ls parameter */
        t->last_file_path = t->r_ctx.file_path_s;
        t->last_file_pid = -1;
        t->last_file_type = t->r_ctx.file_type;
        break;

    case NGX_HTTP_TFS_ACTION_READ_FILE:
    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        t->file.file_offset = t->r_ctx.offset;
        t->file.left_length = t->r_ctx.size;
        break;
    }
}