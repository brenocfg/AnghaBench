#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {size_t segment_index; scalar_t__ left_length; TYPE_6__* segment_data; } ;
struct TYPE_18__ {TYPE_10__* content_type; } ;
struct TYPE_21__ {scalar_t__ sp_curr; scalar_t__ length; int /*<<< orphan*/  log; TYPE_4__ file; int /*<<< orphan*/ * parent; TYPE_2__ headers_in; int /*<<< orphan*/  pool; int /*<<< orphan*/  is_process_meta_seg; int /*<<< orphan*/  state; TYPE_7__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
struct TYPE_17__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_22__ {scalar_t__ oper_size; TYPE_1__ segment_info; } ;
typedef  TYPE_6__ ngx_http_tfs_segment_data_t ;
struct TYPE_25__ {int /*<<< orphan*/  pos; } ;
struct TYPE_23__ {int /*<<< orphan*/  peer_addr_text; TYPE_9__ body_buffer; } ;
typedef  TYPE_7__ ngx_http_tfs_peer_connection_t ;
struct TYPE_19__ {scalar_t__ type; scalar_t__ len; } ;
struct TYPE_24__ {int data_len; TYPE_3__ header; } ;
typedef  TYPE_8__ ngx_http_tfs_ds_read_response_t ;
typedef  TYPE_9__ ngx_buf_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_16__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_AGAIN ; 
 int NGX_HTTP_TFS_EXIT_INVALID_ARGU_ERROR ; 
 int NGX_HTTP_TFS_EXIT_NO_LOGICBLOCK_ERROR ; 
 int NGX_HTTP_TFS_EXIT_PHYSIC_BLOCK_OFFSET_ERROR ; 
 int NGX_HTTP_TFS_EXIT_READ_OFFSET_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_IMAGE_TYPE_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_STATE_READ_DONE ; 
 scalar_t__ NGX_HTTP_TFS_STATUS_MESSAGE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_size (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_clear_buf (TYPE_9__*) ; 
 scalar_t__ ngx_http_tfs_get_content_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_remove_block_cache (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_10__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_tfs_process_ds_input_filter(ngx_http_tfs_t *t)
{
    int16_t                           msg_type;
    uint32_t                          body_len;
    ngx_int_t                         rc;
    ngx_buf_t                        *b;
    ngx_http_tfs_segment_data_t      *segment_data;
    ngx_http_tfs_peer_connection_t   *tp;
    ngx_http_tfs_ds_read_response_t  *resp;

    resp = (ngx_http_tfs_ds_read_response_t *) t->header;
    msg_type = resp->header.type;
    if (msg_type == NGX_HTTP_TFS_STATUS_MESSAGE) {
        t->length = resp->header.len - sizeof(uint32_t);
        return NGX_OK;
    }

    segment_data = &t->file.segment_data[t->file.segment_index];
    tp = t->tfs_peer;
    b = &tp->body_buffer;

    if (resp->data_len < 0) {
        if (resp->data_len == NGX_HTTP_TFS_EXIT_NO_LOGICBLOCK_ERROR) {
            ngx_http_tfs_remove_block_cache(t, segment_data);

        } else if (resp->data_len == -22) {
            /* for compatibility,
             * old dataserver will return this instead of -1007
             */
            resp->data_len = NGX_HTTP_TFS_EXIT_INVALID_ARGU_ERROR;
        }

        /* must be bad request, do not retry */
        if (resp->data_len == NGX_HTTP_TFS_EXIT_READ_OFFSET_ERROR
            || resp->data_len == NGX_HTTP_TFS_EXIT_INVALID_ARGU_ERROR
            || resp->data_len == NGX_HTTP_TFS_EXIT_PHYSIC_BLOCK_OFFSET_ERROR)
        {
            return resp->data_len;
        }
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "read file(block id: %uD, file id: %uL) "
                      "from (%s) fail, error code: %D, will retry",
                      segment_data->segment_info.block_id,
                      segment_data->segment_info.file_id,
                      tp->peer_addr_text, resp->data_len);
        ngx_http_tfs_clear_buf(b);
        return NGX_HTTP_TFS_AGAIN;
    }

    if (resp->data_len == 0) {
        t->state = NGX_HTTP_TFS_STATE_READ_DONE;
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, t->log, 0, "read len is 0");
        return NGX_DONE;
    }

    if (resp->data_len >= NGX_HTTP_TFS_IMAGE_TYPE_SIZE) {
        /* we need to check small file or large file's first data segment */
        /* or custom file's first segment */
        if (((t->parent == NULL && !t->is_process_meta_seg)
             || (t->parent && t->sp_curr == 0))
            && t->headers_in.content_type == NULL)
        {
            if (ngx_buf_size(b) < NGX_HTTP_TFS_IMAGE_TYPE_SIZE) {
                return NGX_AGAIN;
            }

            t->headers_in.content_type = ngx_pcalloc(t->pool, sizeof(ngx_table_elt_t));
            if (t->headers_in.content_type == NULL) {
                return NGX_ERROR;
            }

            rc = ngx_http_tfs_get_content_type(b->pos, &t->headers_in.content_type->value);
            if (rc != NGX_OK) {
                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, t->log, 0, "unknown content type");
            }
        }
    }

    body_len = resp->header.len - sizeof(uint32_t);
    t->length = body_len;
    /* in readv2, body_len = resp->data_len + 40 */
    segment_data->oper_size = resp->data_len;
    /* sub process only read once */
    if (t->parent) {
        t->file.left_length = resp->data_len;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, t->log, 0,
                   "read len is %O, data len is %D",
                   t->length, resp->data_len);

    return NGX_OK;
}