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

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_14__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; } ;
struct TYPE_18__ {int /*<<< orphan*/  pool; TYPE_3__* loc_conf; int /*<<< orphan*/  last_file_type; TYPE_1__ last_file_path; int /*<<< orphan*/  last_file_pid; TYPE_6__ r_ctx; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
typedef  TYPE_6__ ngx_http_tfs_restful_ctx_t ;
struct TYPE_17__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {int file_len; TYPE_4__ header; int /*<<< orphan*/  file_path; int /*<<< orphan*/  pid; int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; } ;
typedef  TYPE_7__ ngx_http_tfs_ms_ls_msg_header_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_21__ {int /*<<< orphan*/ * next; TYPE_9__* buf; } ;
typedef  TYPE_8__ ngx_chain_t ;
struct TYPE_22__ {size_t last; scalar_t__ pos; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_15__ {int /*<<< orphan*/  version; } ;
struct TYPE_16__ {TYPE_2__ meta_server_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_LS_FILEPATH_MESSAGE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 TYPE_8__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_9__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_ls_message(ngx_http_tfs_t *t)
{
    size_t                            size;
    u_char                           *p;
    ngx_buf_t                        *b;
    ngx_chain_t                      *cl;
    ngx_http_tfs_restful_ctx_t       *r_ctx;
    ngx_http_tfs_ms_ls_msg_header_t  *req;

    r_ctx = &t->r_ctx;

    size = sizeof(ngx_http_tfs_ms_ls_msg_header_t) +
        /* file path */
        t->last_file_path.len +
        /* '/0' */
        1 +
        /* file type */
        sizeof(uint8_t) +
        /* version */
        sizeof(uint64_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ms_ls_msg_header_t *) b->pos;
    req->header.type = NGX_HTTP_TFS_LS_FILEPATH_MESSAGE;
    req->header.len = size - sizeof(ngx_http_tfs_header_t);
    req->header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.id = ngx_http_tfs_generate_packet_id();
    req->app_id = r_ctx->app_id;
    req->user_id = r_ctx->user_id;
    req->file_len = t->last_file_path.len + 1;
    req->pid = t->last_file_pid;
    p = ngx_cpymem(req->file_path, t->last_file_path.data,
                   t->last_file_path.len + 1);

    *p = t->last_file_type;
    p += sizeof(uint8_t);

    *((uint64_t *)p) = t->loc_conf->meta_server_table.version;

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