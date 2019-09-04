#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_22__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {size_t size; } ;
struct TYPE_17__ {scalar_t__ size; } ;
struct TYPE_19__ {void* left_length; } ;
struct TYPE_23__ {scalar_t__ read_ver; size_t length; TYPE_4__ stat_info; int /*<<< orphan*/  is_process_meta_seg; scalar_t__ is_large_file; int /*<<< orphan*/  is_stat_dup_file; TYPE_3__* readv2_rsp_tail_buf; int /*<<< orphan*/  pool; TYPE_12__ file_stat; TYPE_2__ file; int /*<<< orphan*/  log; TYPE_7__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
struct TYPE_16__ {scalar_t__ pos; } ;
struct TYPE_24__ {int /*<<< orphan*/  peer_addr_text; TYPE_10__ body_buffer; } ;
typedef  TYPE_7__ ngx_http_tfs_peer_connection_t ;
struct TYPE_25__ {scalar_t__ file_info_len; int /*<<< orphan*/  file_info; } ;
typedef  TYPE_8__ ngx_http_tfs_ds_readv2_response_tail_t ;
struct TYPE_18__ {int type; } ;
struct TYPE_26__ {int /*<<< orphan*/  data_len; TYPE_1__ header; } ;
typedef  TYPE_9__ ngx_http_tfs_ds_read_response_t ;
typedef  TYPE_10__ ngx_buf_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_20__ {void* last; scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_AGAIN ; 
 scalar_t__ NGX_HTTP_TFS_RAW_FILE_INFO_SIZE ; 
 scalar_t__ NGX_HTTP_TFS_READ_V2 ; 
 size_t NGX_HTTP_TFS_READ_V2_TAIL_LEN ; 
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int /*<<< orphan*/  NGX_HTTP_TFS_STATUS_MESSAGE_OK ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 size_t ngx_buf_size (TYPE_10__*) ; 
 void* ngx_cpymem (void*,scalar_t__,size_t) ; 
 void* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_http_tfs_copy_body_buffer (TYPE_6__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_wrap_raw_file_info (int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 void* ngx_min (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_read_message(ngx_http_tfs_t *t)
{
    size_t                                   size, left_len, tail_len;
    int32_t                                  code, err_len;
    uint16_t                                 type;
    ngx_int_t                                rc;
    ngx_str_t                                err_msg;
    ngx_buf_t                               *b;
    ngx_http_tfs_peer_connection_t          *tp;
    ngx_http_tfs_ds_read_response_t         *resp;
    ngx_http_tfs_ds_readv2_response_tail_t  *readv2_rsp_tail;

    resp = (ngx_http_tfs_ds_read_response_t *) t->header;
    tp = t->tfs_peer;
    type = resp->header.type;
    b = &tp->body_buffer;

    switch (type) {
    case NGX_HTTP_TFS_STATUS_MESSAGE:
        /* weird status message, err_code is in resp->data_len */
        code = resp->data_len;
        if (code != NGX_HTTP_TFS_STATUS_MESSAGE_OK) {
            err_len = *(uint32_t*) (b->pos);
            if (err_len > 0) {
                err_msg.data = b->pos + sizeof(uint32_t);
                err_msg.len = err_len;
            }

            ngx_log_error(NGX_LOG_ERR, t->log, 0,
                          "read data (data server: %s) failed, "
                          "error code (%d) err_msg(%V)",
                          tp->peer_addr_text, code, &err_msg);
        }

        return NGX_HTTP_TFS_AGAIN;
    }

    size = ngx_buf_size(b);

    /* read v2 */
    if (t->read_ver == NGX_HTTP_TFS_READ_V2) {
        /* recv file_info */
        if (t->length < 0
            || (size_t) t->length <= NGX_HTTP_TFS_READ_V2_TAIL_LEN)
        {
            t->length -= size;
            if (t->length == 0) {
                t->readv2_rsp_tail_buf->last =
                         ngx_cpymem(t->readv2_rsp_tail_buf->last, b->pos, size);
                readv2_rsp_tail = (ngx_http_tfs_ds_readv2_response_tail_t *)
                                   t->readv2_rsp_tail_buf->pos;
                if (readv2_rsp_tail->file_info_len
                    != NGX_HTTP_TFS_RAW_FILE_INFO_SIZE)
                {
                    return NGX_ERROR;
                }
                ngx_http_tfs_wrap_raw_file_info(&readv2_rsp_tail->file_info, &t->file_stat);
                t->file.left_length = ngx_min(t->file.left_length, (uint64_t)t->file_stat.size);
            }
            return NGX_OK;
        }

        /* recv data only or data + file_info */
        left_len = t->length - size;
        if (left_len < NGX_HTTP_TFS_READ_V2_TAIL_LEN) {
            tail_len = NGX_HTTP_TFS_READ_V2_TAIL_LEN - left_len;
            size -= tail_len;
            t->length -= tail_len;
            /* all recvd */
            if (left_len == 0) {
                readv2_rsp_tail = (ngx_http_tfs_ds_readv2_response_tail_t *)
                                   (b->pos + size);
                /* should not happened */
                if (readv2_rsp_tail->file_info_len
                    != NGX_HTTP_TFS_RAW_FILE_INFO_SIZE)
                {
                    return NGX_ERROR;
                }
                ngx_http_tfs_wrap_raw_file_info(&readv2_rsp_tail->file_info, &t->file_stat);
                t->file.left_length = ngx_min(t->file.left_length, (uint64_t)t->file_stat.size);

            /* all data and partial file_info recvd */
            } else if (left_len > 0) {
                t->readv2_rsp_tail_buf = ngx_create_temp_buf(t->pool,
                                                 NGX_HTTP_TFS_READ_V2_TAIL_LEN);
                if (t->readv2_rsp_tail_buf == NULL) {
                    return NGX_ERROR;
                }
                t->readv2_rsp_tail_buf->last =
                                        ngx_cpymem(t->readv2_rsp_tail_buf->last,
                                                   b->pos + size, tail_len);

            } else {
                return NGX_ERROR;
            }

        /* only data recvd */
        } else if (left_len == NGX_HTTP_TFS_READ_V2_TAIL_LEN) {
            t->readv2_rsp_tail_buf = ngx_create_temp_buf(t->pool,
                                                 NGX_HTTP_TFS_READ_V2_TAIL_LEN);
            if (t->readv2_rsp_tail_buf == NULL) {
                return NGX_ERROR;
            }
        }
    }

    if ((!t->is_large_file && !t->is_stat_dup_file )
        || (t->is_large_file && !t->is_process_meta_seg))
    {
        rc = ngx_http_tfs_copy_body_buffer(t, size, b->pos);
        if (rc == NGX_ERROR) {
            return rc;
        }
    }

    t->stat_info.size += size;
    t->length -= size;

    return NGX_OK;
}