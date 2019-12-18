#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_20__ {size_t segment_count; size_t segment_index; size_t curr_batch_count; int open_mode; } ;
struct TYPE_22__ {TYPE_1__ file; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  block_cache_ctx; int /*<<< orphan*/  name_server_addr; int /*<<< orphan*/  name_server_addr_text; TYPE_5__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_27__ {size_t ds_count; TYPE_11__* ds_addrs; void* lease_id; void* version; } ;
struct TYPE_21__ {size_t block_id; } ;
struct TYPE_23__ {scalar_t__ ds_retry; TYPE_8__ block_info; TYPE_2__ segment_info; } ;
typedef  TYPE_4__ ngx_http_tfs_segment_data_t ;
struct TYPE_19__ {int /*<<< orphan*/ * pos; } ;
struct TYPE_24__ {TYPE_12__ body_buffer; } ;
typedef  TYPE_5__ ngx_http_tfs_peer_connection_t ;
struct TYPE_25__ {size_t block_count; } ;
typedef  TYPE_6__ ngx_http_tfs_ns_batch_block_info_response_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_26__ {int type; } ;
typedef  TYPE_7__ ngx_http_tfs_header_t ;
typedef  TYPE_8__ ngx_http_tfs_block_info_t ;
struct TYPE_28__ {size_t ds_count; int /*<<< orphan*/ * ds_addrs; } ;
typedef  TYPE_9__ ngx_http_tfs_block_cache_value_t ;
struct TYPE_17__ {size_t block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_10__ ngx_http_tfs_block_cache_key_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  void* int32_t ;
struct TYPE_18__ {size_t ip; size_t port; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_AGAIN ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_EXIT_GENERAL_ERROR ; 
 size_t NGX_HTTP_TFS_MAX_BATCH_COUNT ; 
 int NGX_HTTP_TFS_OPEN_MODE_READ ; 
 int NGX_HTTP_TFS_OPEN_MODE_WRITE ; 
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_block_cache_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_status_message (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t,size_t,void*,void*) ; 
 TYPE_11__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

ngx_int_t
ngx_http_tfs_parse_batch_block_info_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    u_char                                       *p;
    uint16_t                                      type;
    uint32_t                                      block_count, complete_count,
                                                  ds_count, block_id;
    ngx_str_t                                     err_msg;
    ngx_uint_t                                    i, j, k;
    ngx_http_tfs_header_t                        *header;
    ngx_http_tfs_block_info_t                    *block_info;
    ngx_http_tfs_peer_connection_t               *tp;
    ngx_http_tfs_block_cache_key_t                key;
    ngx_http_tfs_block_cache_value_t              value;
    ngx_http_tfs_ns_batch_block_info_response_t  *resp;

    header = (ngx_http_tfs_header_t *) t->header;
    tp = t->tfs_peer;
    type = header->type;

    switch (type) {
    case NGX_HTTP_TFS_STATUS_MESSAGE:
        ngx_str_set(&err_msg, "batch get block info (name server)");
        return ngx_http_tfs_status_message(&tp->body_buffer, &err_msg, t->log);
    }

    resp = (ngx_http_tfs_ns_batch_block_info_response_t *) tp->body_buffer.pos;

    p = tp->body_buffer.pos
         + sizeof(ngx_http_tfs_ns_batch_block_info_response_t);

    block_count = t->file.segment_count - t->file.segment_index;
    if (block_count > NGX_HTTP_TFS_MAX_BATCH_COUNT) {
        block_count = NGX_HTTP_TFS_MAX_BATCH_COUNT;
    }
    t->file.curr_batch_count = resp->block_count;

    for (i = 0; i < resp->block_count; i++) {
        j = i;
        /* block id */
        block_id = *(uint32_t *) p;
        p += sizeof(uint32_t);
        /* read need find the right segment according to block id */
        if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_READ) {
            for (j = 0; j < block_count; j++) {
                if (segment_data[j].segment_info.block_id == block_id) {
                    break;
                }
            }
            if (j == block_count) {
                return NGX_HTTP_TFS_AGAIN;
            }
        }
        segment_data[j].segment_info.block_id = block_id;

        block_info = &segment_data[j].block_info;

        /* ds count */
        ds_count = *(uint32_t *) p;
        p += sizeof(uint32_t);

        if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_WRITE) {
            if (ds_count <= 3) {
                return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
            }

            /* flag version leaseid */
            block_info->ds_count = ds_count - 3;

        } else {
            if (ds_count < 1) {
                return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
            }

            block_info->ds_count = ds_count;
        }

        block_info->ds_addrs = ngx_pcalloc(t->pool,
                                        sizeof(ngx_http_tfs_inet_t) * ds_count);
        if (block_info->ds_addrs == NULL) {
            return NGX_ERROR;
        }

        for (k = 0; k < block_info->ds_count; k++) {
            block_info->ds_addrs[k].ip = *(uint32_t *) p;
            block_info->ds_addrs[k].port = *(uint32_t *) (p + sizeof(uint32_t));

            p += sizeof(uint32_t) * 2;
        }

        if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_WRITE) {
            /* flag */
            p += sizeof(uint64_t);
            /* version */
            block_info->version = *((int32_t *) p);
            p += sizeof(int64_t);
            /* lease id */
            block_info->lease_id = *((int32_t *) p);
            p += sizeof(int64_t);
        }

        ngx_log_debug5(NGX_LOG_DEBUG_HTTP, t->log, 0,
                       "batch get block info from nameserver: "
                       "%V, block id: %uD, "
                       "ds count: %uD, version: %D, lease id: %D",
                       &t->name_server_addr_text, block_id,
                       block_info->ds_count,
                       block_info->version, block_info->lease_id);

        /* insert block cache  */
        if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_READ) {
            key.ns_addr = *((uint64_t *)(&t->name_server_addr));
            key.block_id = block_id;
            value.ds_count = block_info->ds_count;
            value.ds_addrs = (uint64_t *)block_info->ds_addrs;
            ngx_http_tfs_block_cache_insert(&t->block_cache_ctx,
                                            t->pool, t->log, &key, &value);
        }

        /* reset segment status */
        segment_data[j].ds_retry = 0;
    }

    /* check if all semgents complete */
    if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_READ) {
        complete_count = 0;
        for (i = 0; i < block_count; i++) {
            if (segment_data[i].block_info.ds_addrs != NULL) {
                complete_count++;
                continue;
            }

            /* maybe has duplicate block, find in already complete segment */
            for (j = 0; j < i; j++) {
                if (segment_data[i].segment_info.block_id
                    != segment_data[j].segment_info.block_id)
                {
                    continue;
                }

                /* TODO: check this */
                segment_data[i].block_info = segment_data[j].block_info;
                segment_data[i].ds_retry = 0;
                complete_count++;
                break;
            }
        }
        if (complete_count != block_count) {
            return NGX_HTTP_TFS_AGAIN;
        }
    }

    return NGX_OK;
}