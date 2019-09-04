#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_13__ {scalar_t__ segment_count; size_t segment_index; int open_mode; TYPE_5__* segment_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  pool; TYPE_1__ file; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_14__ {scalar_t__ block_id; } ;
struct TYPE_17__ {scalar_t__ cache_hit; TYPE_2__ segment_info; } ;
typedef  TYPE_5__ ngx_http_tfs_segment_data_t ;
struct TYPE_15__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {int mode; TYPE_3__ header; scalar_t__* block_ids; scalar_t__ block_count; } ;
typedef  TYPE_6__ ngx_http_tfs_ns_batch_block_info_request_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_19__ {int /*<<< orphan*/ * next; TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_20__ {size_t last; scalar_t__ pos; } ;
typedef  TYPE_8__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_BATCH_GET_BLOCK_INFO_MESSAGE ; 
 scalar_t__ NGX_HTTP_TFS_MAX_BATCH_COUNT ; 
 scalar_t__ NGX_HTTP_TFS_NO_BLOCK_CACHE ; 
 int NGX_HTTP_TFS_OPEN_MODE_READ ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_batch_block_info_message(ngx_http_tfs_t *t)
{
    size_t                                       size;
    uint32_t                                     block_count, real_block_count;
    ngx_uint_t                                   i, j;
    ngx_buf_t                                   *b;
    ngx_chain_t                                 *cl;
    ngx_http_tfs_segment_data_t                 *segment_data;
    ngx_http_tfs_ns_batch_block_info_request_t  *req;

    block_count = t->file.segment_count - t->file.segment_index;
    if (block_count > NGX_HTTP_TFS_MAX_BATCH_COUNT) {
        block_count = NGX_HTTP_TFS_MAX_BATCH_COUNT;
    }

    real_block_count = block_count;
    if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_READ) {
        segment_data = &t->file.segment_data[t->file.segment_index];
        for (i = 0; i < block_count; i++, segment_data++) {
            if (segment_data->cache_hit != NGX_HTTP_TFS_NO_BLOCK_CACHE) {
                real_block_count--;
            }
        }
    }

    size = sizeof(ngx_http_tfs_ns_batch_block_info_request_t)
            + real_block_count * sizeof(uint32_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ns_batch_block_info_request_t *) b->pos;

    req->header.type = NGX_HTTP_TFS_BATCH_GET_BLOCK_INFO_MESSAGE;
    req->header.len = size - sizeof(ngx_http_tfs_header_t);
    req->header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.id = ngx_http_tfs_generate_packet_id();
    req->mode = t->file.open_mode;
    req->block_count = real_block_count;
    segment_data = &t->file.segment_data[t->file.segment_index];
    for (i = 0, j = 0; i < block_count; i++, segment_data++) {
        if (t->file.open_mode & NGX_HTTP_TFS_OPEN_MODE_READ) {
            if (segment_data->cache_hit == NGX_HTTP_TFS_NO_BLOCK_CACHE) {
                req->block_ids[j++] = segment_data->segment_info.block_id;
            }

        } else {
            req->block_ids[i] = 0;
        }
    }
    req->header.crc = ngx_http_tfs_crc(NGX_HTTP_TFS_PACKET_FLAG,
                                       (const char *) (&req->header + 1),
                                       req->header.len);

    b->last += size;

    cl = ngx_alloc_chain_link(t->pool);
    if (cl == NULL) {
        return NULL;
    }

    cl->buf = b;
    cl->next = NULL;

    return cl;
}