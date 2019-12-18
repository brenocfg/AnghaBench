#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {int offset; int size; int u_size; int modify_time; int create_time; scalar_t__ crc; int /*<<< orphan*/  flag; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {int /*<<< orphan*/  fsname; } ;
struct TYPE_17__ {TYPE_9__ file_stat; TYPE_1__ r_ctx; int /*<<< orphan*/  is_large_file; int /*<<< orphan*/  log; TYPE_5__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_segment_head_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_segment_data_t ;
struct TYPE_13__ {scalar_t__ pos; } ;
struct TYPE_18__ {TYPE_10__ body_buffer; } ;
typedef  TYPE_5__ ngx_http_tfs_peer_connection_t ;
struct TYPE_19__ {int type; } ;
typedef  TYPE_6__ ngx_http_tfs_header_t ;
struct TYPE_20__ {scalar_t__ data_len; int /*<<< orphan*/  file_info; } ;
typedef  TYPE_7__ ngx_http_tfs_ds_stat_response_t ;
struct TYPE_16__ {int size; } ;
struct TYPE_15__ {int u_size; } ;
struct TYPE_21__ {int data_len; scalar_t__ file_info_len; TYPE_3__ seg_head; TYPE_2__ file_info; } ;
typedef  TYPE_8__ ngx_http_tfs_ds_sp_readv2_response_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_AGAIN ; 
 int NGX_HTTP_TFS_EXIT_FILE_INFO_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_EXIT_GENERAL_ERROR ; 
 int NGX_HTTP_TFS_EXIT_NO_LOGICBLOCK_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_FILE_DELETED ; 
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_get_file_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_remove_block_cache (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_status_message (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_wrap_raw_file_info (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_statfile_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    uint16_t                               type;
    ngx_int_t                              rc;
    ngx_str_t                              action;
    ngx_http_tfs_header_t                 *header;
    ngx_http_tfs_peer_connection_t        *tp;
    ngx_http_tfs_ds_stat_response_t       *resp;
    ngx_http_tfs_ds_sp_readv2_response_t  *resp2;


    header = (ngx_http_tfs_header_t *) t->header;
    tp = t->tfs_peer;
    type = header->type;

    switch (type) {
    case NGX_HTTP_TFS_STATUS_MESSAGE:
        ngx_str_set(&action, "stat file(data server)");
        rc = ngx_http_tfs_status_message(&tp->body_buffer, &action, t->log);
        return rc;
    }

    if (!t->is_large_file) {
        resp = (ngx_http_tfs_ds_stat_response_t *) tp->body_buffer.pos;
        if (resp->data_len <= 0) {
            return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
        }
        ngx_http_tfs_wrap_raw_file_info(&resp->file_info, &t->file_stat);

    } else {
        resp2 = (ngx_http_tfs_ds_sp_readv2_response_t *) tp->body_buffer.pos;
        if (resp2->data_len == NGX_HTTP_TFS_EXIT_NO_LOGICBLOCK_ERROR) {
            ngx_http_tfs_remove_block_cache(t, segment_data);
            return NGX_HTTP_TFS_AGAIN;
        }

        /* file deleted */
        if (resp2->data_len == NGX_HTTP_TFS_EXIT_FILE_INFO_ERROR) {
            t->file_stat.id =
                     ngx_http_tfs_raw_fsname_get_file_id(t->r_ctx.fsname);
            t->file_stat.offset = -1;
            t->file_stat.size = -1;
            t->file_stat.u_size = -1;
            t->file_stat.modify_time = -1;
            t->file_stat.create_time = -1;
            t->file_stat.flag = NGX_HTTP_TFS_FILE_DELETED;
            t->file_stat.crc = 0;

        } else {
            if (resp2->data_len != sizeof(ngx_http_tfs_segment_head_t)
                || resp2->file_info_len <= 0)
            {
                return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
            }
            t->file_stat.size = resp2->seg_head.size;
            t->file_stat.u_size =
                                 resp2->file_info.u_size + resp2->seg_head.size;
        }

    }

    return NGX_OK;
}