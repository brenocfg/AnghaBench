#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_40__ {size_t segment_index; scalar_t__ left_length; int /*<<< orphan*/  file_hole_size; int /*<<< orphan*/  file_offset; TYPE_9__* segment_data; } ;
struct TYPE_38__ {int /*<<< orphan*/  save_body_buffer; } ;
struct TYPE_37__ {scalar_t__ size; } ;
struct TYPE_34__ {int code; } ;
struct TYPE_36__ {int version; int /*<<< orphan*/  read_stat_type; int /*<<< orphan*/  chk_exist; TYPE_1__ action; } ;
struct TYPE_35__ {int /*<<< orphan*/  size; } ;
struct TYPE_41__ {void* read_ver; int header_size; TYPE_7__ file; TYPE_6__* tfs_peer; TYPE_5__ dedup_ctx; int /*<<< orphan*/  use_dedup; int /*<<< orphan*/  is_large_file; TYPE_10__* meta_segment_data; int /*<<< orphan*/  free_bufs; int /*<<< orphan*/  pool; TYPE_4__ file_stat; int /*<<< orphan*/  state; TYPE_3__ r_ctx; TYPE_2__ stat_info; int /*<<< orphan*/  parent; int /*<<< orphan*/  is_process_meta_seg; int /*<<< orphan*/ * json_output; int /*<<< orphan*/  log; } ;
typedef  TYPE_8__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_segment_head_t ;
struct TYPE_42__ {int oper_size; } ;
typedef  TYPE_9__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_ds_read_response_t ;
struct TYPE_33__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_10__ ngx_chain_t ;
struct TYPE_39__ {int /*<<< orphan*/  body_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 139 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 138 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 137 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 136 
 scalar_t__ NGX_HTTP_TFS_MAX_FRAGMENT_SIZE ; 
 scalar_t__ NGX_HTTP_TFS_MAX_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_NO ; 
 void* NGX_HTTP_TFS_READ ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_READ_STAT_FORCE ; 
 void* NGX_HTTP_TFS_READ_V2 ; 
#define  NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA 135 
#define  NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT 134 
#define  NGX_HTTP_TFS_STATE_REMOVE_STAT_FILE 133 
#define  NGX_HTTP_TFS_STATE_WRITE_CLOSE_FILE 132 
#define  NGX_HTTP_TFS_STATE_WRITE_CREATE_FILE_NAME 131 
#define  NGX_HTTP_TFS_STATE_WRITE_DELETE_DATA 130 
#define  NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE 129 
#define  NGX_HTTP_TFS_STATE_WRITE_WRITE_DATA 128 
 TYPE_10__* ngx_http_tfs_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_10__* ngx_http_tfs_create_closefile_message (TYPE_8__*,TYPE_9__*) ; 
 TYPE_10__* ngx_http_tfs_create_createfile_message (TYPE_8__*,TYPE_9__*) ; 
 TYPE_10__* ngx_http_tfs_create_read_message (TYPE_8__*,TYPE_9__*,void*,int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_http_tfs_create_stat_message (TYPE_8__*,TYPE_9__*) ; 
 TYPE_10__* ngx_http_tfs_create_unlink_message (TYPE_8__*,TYPE_9__*) ; 
 TYPE_10__* ngx_http_tfs_create_write_message (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_fill_file_hole (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_tfs_json_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_chain_t *
ngx_http_tfs_data_server_create_message(ngx_http_tfs_t *t)
{
    uint32_t                      meta_segment_size;
    uint16_t                      action;
    ngx_int_t                     rc;
    ngx_chain_t                  *cl;
    ngx_http_tfs_segment_data_t  *segment_data;

    cl = NULL;
    meta_segment_size = 0;
    action = t->r_ctx.action.code;
    segment_data = &t->file.segment_data[t->file.segment_index];

    switch (action) {
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
        if (t->r_ctx.chk_exist == NGX_HTTP_TFS_NO) {
            t->json_output = ngx_http_tfs_json_init(t->log, t->pool);
            if (t->json_output == NULL) {
                return NULL;
            }
        }
        if (t->is_large_file) {
            segment_data->oper_size = sizeof(ngx_http_tfs_segment_head_t);
            return ngx_http_tfs_create_read_message(t, segment_data,
                            NGX_HTTP_TFS_READ_V2, NGX_HTTP_TFS_READ_STAT_FORCE);
        }

        return ngx_http_tfs_create_stat_message(t, segment_data);

    case NGX_HTTP_TFS_ACTION_READ_FILE:
        t->read_ver = NGX_HTTP_TFS_READ;
        t->header_size = sizeof(ngx_http_tfs_ds_read_response_t);
        /* large file need read meta segment first */
        if (t->is_large_file && t->is_process_meta_seg) {
            if (t->meta_segment_data == NULL) {
                /* for files smaller than 140GB, 2MB is fairly enough */
                cl = ngx_http_tfs_chain_get_free_buf(t->pool, &t->free_bufs,
                    NGX_HTTP_TFS_MAX_FRAGMENT_SIZE);
                if (cl == NULL) {
                    return NULL;
                }
                t->tfs_peer->body_buffer = *(cl->buf);
                t->meta_segment_data = cl;
            }
        }

        /* use readv2 if read from start */
        /* unless is large file data segment */
        if (t->r_ctx.version == 1
            && t->file.file_offset == 0
            && !t->parent)
        {
            t->read_ver = NGX_HTTP_TFS_READ_V2;
        }
        /* custom file need fill file hole */
        if (t->r_ctx.version == 2 && t->file.file_hole_size > 0) {
            rc = ngx_http_tfs_fill_file_hole(t, t->file.file_hole_size);
            if (rc == NGX_ERROR) {
                return NULL;
            }
            t->stat_info.size += t->file.file_hole_size;
            t->file.file_hole_size = 0;
        }
        return ngx_http_tfs_create_read_message(t, segment_data,
                                                t->read_ver,
                                                t->r_ctx.read_stat_type);
    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_WRITE_STAT_DUP_FILE:
            return ngx_http_tfs_create_stat_message(t, segment_data);
        case NGX_HTTP_TFS_STATE_WRITE_CREATE_FILE_NAME:
            return ngx_http_tfs_create_createfile_message(t, segment_data);
        case NGX_HTTP_TFS_STATE_WRITE_WRITE_DATA:
            return ngx_http_tfs_create_write_message(t, segment_data);
        case NGX_HTTP_TFS_STATE_WRITE_CLOSE_FILE:
            return ngx_http_tfs_create_closefile_message(t, segment_data);
        case NGX_HTTP_TFS_STATE_WRITE_DELETE_DATA:
            return ngx_http_tfs_create_unlink_message(t, segment_data);
        default:
            return NULL;
        }

    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        switch(t->state) {
        case NGX_HTTP_TFS_STATE_REMOVE_STAT_FILE:
            return ngx_http_tfs_create_stat_message(t, segment_data);

        case NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT:
            t->read_ver = NGX_HTTP_TFS_READ;
            if (t->meta_segment_data == NULL) {
                if (t->use_dedup) {
                    meta_segment_size = t->file_stat.size;
                    t->file.left_length = t->file_stat.size;
                }
                /* if is large file, for files smaller than 140GB,
                 * 2MB is fairly enough
                 */
                if (t->is_large_file) {
                    meta_segment_size = NGX_HTTP_TFS_MAX_FRAGMENT_SIZE;
                    t->file.left_length = NGX_HTTP_TFS_MAX_SIZE;
                }
                cl = ngx_http_tfs_chain_get_free_buf(t->pool, &t->free_bufs,
                    meta_segment_size);
                if (cl == NULL) {
                    return NULL;
                }
                t->meta_segment_data = cl;

                /* avoid alloc body_buffer twice */
                if (!t->is_large_file && t->use_dedup) {
                    t->dedup_ctx.save_body_buffer = t->tfs_peer->body_buffer;
                }

                t->tfs_peer->body_buffer = *(cl->buf);
            }
            t->header_size = sizeof(ngx_http_tfs_ds_read_response_t);

            /* use readv2 to get file size if we do not know that */
            if (t->file.left_length == NGX_HTTP_TFS_MAX_SIZE) {
                t->read_ver = NGX_HTTP_TFS_READ_V2;
            }
            return ngx_http_tfs_create_read_message(t, segment_data,
                                     t->read_ver, NGX_HTTP_TFS_READ_STAT_FORCE);
        case NGX_HTTP_TFS_STATE_REMOVE_DELETE_DATA:
            return ngx_http_tfs_create_unlink_message(t, segment_data);

        default:
            return NULL;
        }
    }

    return cl;
}