#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_23__ {int version; int /*<<< orphan*/  unlink_type; } ;
struct TYPE_21__ {int /*<<< orphan*/  segment_index; } ;
struct TYPE_24__ {int /*<<< orphan*/  pool; TYPE_5__ r_ctx; TYPE_3__ file; int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
struct TYPE_22__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_27__ {int ds_count; int version; int lease_id; int /*<<< orphan*/ * ds_addrs; } ;
struct TYPE_25__ {TYPE_4__ segment_info; TYPE_9__ block_info; } ;
typedef  TYPE_7__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_19__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {TYPE_1__ base_header; int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_26__ {TYPE_2__ header; int /*<<< orphan*/  server_mode; } ;
typedef  TYPE_8__ ngx_http_tfs_ds_unlink_request_t ;
typedef  TYPE_9__ ngx_http_tfs_block_info_t ;
struct TYPE_17__ {TYPE_11__* buf; int /*<<< orphan*/ * next; } ;
typedef  TYPE_10__ ngx_chain_t ;
struct TYPE_18__ {size_t last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_11__ ngx_buf_t ;

/* Variables and functions */
 int NGX_HTTP_TFS_FILE_DEFAULT_OPTION ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_REMOVE_FILE_MASTER ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_UNLINK_DELETE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_UNLINK_FILE_MESSAGE ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_10__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_11__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_unlink_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    u_char                            *p;
    size_t                             size;
    ngx_buf_t                         *b;
    ngx_uint_t                         i;
    ngx_chain_t                       *cl;
    ngx_http_tfs_block_info_t         *block_info;
    ngx_http_tfs_ds_unlink_request_t  *req;

    block_info = &segment_data->block_info;
    size = sizeof(ngx_http_tfs_ds_unlink_request_t) +
        /* ds count */
        sizeof(uint32_t) +
        /* ds list */
        block_info->ds_count * sizeof(uint64_t) +
        /* flag verion lease_id */
        sizeof(uint64_t) * 3  +
        /* option flag */
        sizeof(uint32_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ds_unlink_request_t *) b->pos;

    req->header.base_header.type = NGX_HTTP_TFS_UNLINK_FILE_MESSAGE;
    req->header.base_header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.base_header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.base_header.id = ngx_http_tfs_generate_packet_id();
    req->header.base_header.len = size - sizeof(ngx_http_tfs_header_t);
    req->header.block_id = segment_data->segment_info.block_id;
    req->header.file_id = segment_data->segment_info.file_id;
    req->server_mode = NGX_HTTP_TFS_REMOVE_FILE_MASTER;
    if (t->r_ctx.version == 1) {
        req->server_mode |= t->r_ctx.unlink_type;

    } else if (t->r_ctx.version == 2) {
        req->server_mode |= NGX_HTTP_TFS_UNLINK_DELETE;
    }

    p = b->pos + sizeof(ngx_http_tfs_ds_unlink_request_t);

    /* ds count */
    *((uint32_t *) p) = 3 + block_info->ds_count;
    p += sizeof(uint32_t);
    /* ds list */
    for (i = 0; i < block_info->ds_count; i++) {
        *((uint64_t *) p) = *((uint64_t *)&block_info->ds_addrs[i]);
        p += sizeof(uint64_t);
    }

    /* flag, useless */
    *((uint64_t *) p) = -1;
    p += sizeof(uint64_t);
    /* version */
    *((uint64_t *) p) = block_info->version;
    p += sizeof(uint64_t);
    /* lease id */
    *((uint64_t *) p) = block_info->lease_id;
    p += sizeof(uint64_t);

    /* option */
    *((uint32_t *) p) = NGX_HTTP_TFS_FILE_DEFAULT_OPTION;

    req->header.base_header.crc = ngx_http_tfs_crc(NGX_HTTP_TFS_PACKET_FLAG,
                                  (const char *) (&req->header.base_header + 1),
                                  (size - sizeof(ngx_http_tfs_header_t)));

    b->last += size;

    ngx_log_error(NGX_LOG_INFO, t->log, 0,
                  "unlink segment index %uD, block id: %uD, "
                  "file id: %uL, type: %i",
                  t->file.segment_index,
                  segment_data->segment_info.block_id,
                  segment_data->segment_info.file_id, t->r_ctx.unlink_type);

    cl = ngx_alloc_chain_link(t->pool);
    if (cl == NULL) {
        return NULL;
    }
    cl->next = NULL;
    cl->buf = b;
    return cl;
}