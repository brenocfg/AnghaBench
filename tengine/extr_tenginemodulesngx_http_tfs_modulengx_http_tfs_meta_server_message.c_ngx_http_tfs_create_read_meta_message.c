#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_16__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_22__ {TYPE_1__ file_path_s; int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; } ;
struct TYPE_21__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  has_split_frag; int /*<<< orphan*/  log; TYPE_4__* main_conf; TYPE_3__* loc_conf; TYPE_7__ r_ctx; } ;
typedef  TYPE_6__ ngx_http_tfs_t ;
typedef  TYPE_7__ ngx_http_tfs_restful_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_ms_read_response_t ;
struct TYPE_20__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_23__ {int file_len; TYPE_5__ header; int /*<<< orphan*/  file_path_s; int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; } ;
typedef  TYPE_8__ ngx_http_tfs_ms_base_msg_header_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_meta_frag_meta_info_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_24__ {int /*<<< orphan*/ * next; TYPE_10__* buf; } ;
typedef  TYPE_9__ ngx_chain_t ;
struct TYPE_15__ {size_t last; scalar_t__ pos; } ;
typedef  TYPE_10__ ngx_buf_t ;
typedef  size_t int64_t ;
struct TYPE_19__ {int body_buffer_size; } ;
struct TYPE_17__ {size_t version; } ;
struct TYPE_18__ {TYPE_2__ meta_server_table; } ;

/* Variables and functions */
 size_t NGX_HTTP_TFS_MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_NO ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_READ_FILEPATH_MESSAGE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_9__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_10__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,size_t) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_read_meta_message(ngx_http_tfs_t *t, int64_t req_offset,
    uint64_t req_size)
{
    u_char                             *p;
    size_t                              size, max_frag_count, req_frag_count;
    ngx_buf_t                          *b;
    ngx_chain_t                        *cl;
    ngx_http_tfs_restful_ctx_t         *r_ctx;
    ngx_http_tfs_ms_base_msg_header_t  *req;

    r_ctx = &t->r_ctx;

    size = sizeof(ngx_http_tfs_ms_base_msg_header_t) +
        /* file */
        r_ctx->file_path_s.len +
        /* \0 */
        1 +
        /* version */
        sizeof(uint64_t) +
        /* offset */
        sizeof(uint64_t) +
        /* size */
        sizeof(uint64_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ms_base_msg_header_t *) b->pos;
    req->header.type = NGX_HTTP_TFS_READ_FILEPATH_MESSAGE;
    req->header.len = size - sizeof(ngx_http_tfs_header_t);
    req->header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.id = ngx_http_tfs_generate_packet_id();
    req->app_id = r_ctx->app_id;
    req->user_id = r_ctx->user_id;
    req->file_len = r_ctx->file_path_s.len + 1;
    p = ngx_cpymem(req->file_path_s, r_ctx->file_path_s.data,
                   r_ctx->file_path_s.len + 1);

    *((uint64_t *)p) = t->loc_conf->meta_server_table.version;
    p += sizeof(uint64_t);

    *((uint64_t *) p) = req_offset;
    p += sizeof(uint64_t);

    max_frag_count = (t->main_conf->body_buffer_size
                      - sizeof(ngx_http_tfs_ms_read_response_t))
        / sizeof(ngx_http_tfs_meta_frag_meta_info_t);
    req_frag_count = req_size / (NGX_HTTP_TFS_MAX_FRAGMENT_SIZE);

    ngx_log_error(NGX_LOG_INFO, t->log, 0 ,
                  "max_frag_count: %uz, req_frag_count: %uz, data size: %uz",
                  max_frag_count, req_frag_count, req_size);

    if (req_frag_count > max_frag_count) {
        *((uint64_t *) p) =
            (max_frag_count - 1) * NGX_HTTP_TFS_MAX_FRAGMENT_SIZE;
        t->has_split_frag = NGX_HTTP_TFS_YES;

    } else {
        *((uint64_t *) p) = req_size;
        t->has_split_frag = NGX_HTTP_TFS_NO;
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