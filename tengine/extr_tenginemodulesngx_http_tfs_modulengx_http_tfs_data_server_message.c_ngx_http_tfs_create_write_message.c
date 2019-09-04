#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u_char ;
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {int /*<<< orphan*/  segment_index; } ;
struct TYPE_28__ {TYPE_3__ file; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
struct TYPE_27__ {int /*<<< orphan*/  crc; int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_32__ {int ds_count; int version; int lease_id; int /*<<< orphan*/ * ds_addrs; } ;
struct TYPE_29__ {TYPE_4__ segment_info; TYPE_10__* data; scalar_t__ oper_size; int /*<<< orphan*/  write_file_number; int /*<<< orphan*/  oper_offset; TYPE_9__ block_info; } ;
typedef  TYPE_6__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_24__ {int crc; scalar_t__ len; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_25__ {TYPE_1__ base_header; int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_30__ {TYPE_2__ header; scalar_t__ length; int /*<<< orphan*/  offset; int /*<<< orphan*/  file_number; scalar_t__ is_server; } ;
typedef  TYPE_7__ ngx_http_tfs_ds_write_request_t ;
struct TYPE_31__ {int crc; int /*<<< orphan*/  data_crc; } ;
typedef  TYPE_8__ ngx_http_tfs_crc_t ;
typedef  TYPE_9__ ngx_http_tfs_block_info_t ;
struct TYPE_22__ {struct TYPE_22__* next; TYPE_11__* buf; } ;
typedef  TYPE_10__ ngx_chain_t ;
struct TYPE_23__ {int* pos; size_t last; } ;
typedef  TYPE_11__ ngx_buf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_TFS_MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_WRITE_DATA_MESSAGE ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_11__* ngx_alloc_buf (int /*<<< orphan*/ ) ; 
 void* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 size_t ngx_buf_size (TYPE_11__*) ; 
 TYPE_11__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_http_tfs_compute_buf_crc (TYPE_8__*,TYPE_11__*,size_t,int /*<<< orphan*/ ) ; 
 int ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_11__*,TYPE_11__*,int) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_write_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    u_char                           *p, exit;
    size_t                            size, body_size, b_size;
    uint32_t                          crc;
    ngx_int_t                         rc;
    ngx_buf_t                        *b;
    ngx_uint_t                        i;
    ngx_chain_t                      *cl, *body, *ch;
    ngx_http_tfs_crc_t                t_crc;
    ngx_http_tfs_block_info_t        *block_info;
    ngx_http_tfs_ds_write_request_t  *req;

    exit = 0;

    block_info = &segment_data->block_info;
    size = sizeof(ngx_http_tfs_ds_write_request_t) +
        /* ds count */
        sizeof(uint32_t) +
        /* ds list */
        block_info->ds_count * sizeof(uint64_t) +
        /* flag verion lease_id */
        sizeof(uint64_t) * 3 ;

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ds_write_request_t *) b->pos;

    req->header.base_header.type = NGX_HTTP_TFS_WRITE_DATA_MESSAGE;
    req->header.base_header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.base_header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.base_header.id = ngx_http_tfs_generate_packet_id();
    req->header.block_id = segment_data->segment_info.block_id;
    req->header.file_id = segment_data->segment_info.file_id;
    req->offset = segment_data->oper_offset;
    req->is_server = 0;
    req->file_number = segment_data->write_file_number;

    p = b->pos + sizeof(ngx_http_tfs_ds_write_request_t);

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
    b->last += size;

    req->length = segment_data->oper_size;

    crc = ngx_http_tfs_crc(NGX_HTTP_TFS_PACKET_FLAG,
                           (const char *) (&req->header.base_header + 1),
                           (size - sizeof(ngx_http_tfs_header_t)));

    cl = ngx_alloc_chain_link(t->pool);
    if (cl == NULL) {
        return NULL;
    }
    ch = cl;
    cl->buf = b;

    body_size = 0;
    body = segment_data->data;

    t_crc.crc = crc;
    t_crc.data_crc = segment_data->segment_info.crc;

    /* body buf is one or two bufs,
     * please see ngx_http_read_client_request_body
     */
    while (body) {
        b_size = ngx_buf_size(body->buf);
        body_size += b_size;

        b = ngx_alloc_buf(t->pool);
        if (b == NULL) {
            return NULL;
        }

        ngx_memcpy(b, body->buf, sizeof(ngx_buf_t));

        if (body_size > NGX_HTTP_TFS_MAX_FRAGMENT_SIZE) {
            /* need more writes*/
            body_size -= b_size;
            b_size = NGX_HTTP_TFS_MAX_FRAGMENT_SIZE - body_size;
            body_size = NGX_HTTP_TFS_MAX_FRAGMENT_SIZE;
            exit = 1;
        }

        rc = ngx_http_tfs_compute_buf_crc(&t_crc, b, b_size, t->log);
        if (rc == NGX_ERROR) {
            return NULL;
        }

        cl->next = ngx_alloc_chain_link(t->pool);
        if (cl->next == NULL) {
            return NULL;
        }

        cl = cl->next;
        cl->buf = b;

        if (exit) {
            break;
        }

        body = body->next;
    }
    cl->next = NULL;

    ngx_log_error(NGX_LOG_INFO, t->log, 0,
                  "write segment index %uD, block id: %uD, file id: %uL, "
                  "offset: %D, length: %uD, crc: %uD",
                  t->file.segment_index, segment_data->segment_info.block_id,
                  segment_data->segment_info.file_id, req->offset,
                  req->length, t_crc.data_crc);

    segment_data->segment_info.crc = t_crc.data_crc;
    req->header.base_header.len = size - sizeof(ngx_http_tfs_header_t)
                                   + req->length;
    req->header.base_header.crc = t_crc.crc;

    return ch;
}