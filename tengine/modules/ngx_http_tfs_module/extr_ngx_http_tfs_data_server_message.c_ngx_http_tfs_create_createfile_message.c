#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_13__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_16__ {TYPE_1__ segment_info; } ;
typedef  TYPE_4__ ngx_http_tfs_segment_data_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_14__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_17__ {TYPE_2__ base_header; int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
typedef  TYPE_5__ ngx_http_tfs_ds_msg_header_t ;
struct TYPE_18__ {int /*<<< orphan*/ * next; TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_19__ {size_t last; scalar_t__ pos; } ;
typedef  TYPE_7__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_CREATE_FILENAME_MESSAGE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 TYPE_6__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_createfile_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    size_t                         size;
    ngx_buf_t                     *b;
    ngx_chain_t                   *cl;
    ngx_http_tfs_ds_msg_header_t  *req;

    size = sizeof(ngx_http_tfs_ds_msg_header_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ds_msg_header_t *) b->pos;

    req->base_header.type = NGX_HTTP_TFS_CREATE_FILENAME_MESSAGE;
    req->base_header.len = size - sizeof(ngx_http_tfs_header_t);
    req->base_header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->base_header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->base_header.id = ngx_http_tfs_generate_packet_id();
    req->block_id = segment_data->segment_info.block_id;
    req->file_id = segment_data->segment_info.file_id;

    req->base_header.crc = ngx_http_tfs_crc(NGX_HTTP_TFS_PACKET_FLAG,
                                         (const char *) (&req->base_header + 1),
                                         req->base_header.len);

    b->last += size;

    cl = ngx_alloc_chain_link(t->pool);
    if (cl == NULL) {
        return NULL;
    }

    cl->buf = b;
    cl->next = NULL;
    return cl;
}