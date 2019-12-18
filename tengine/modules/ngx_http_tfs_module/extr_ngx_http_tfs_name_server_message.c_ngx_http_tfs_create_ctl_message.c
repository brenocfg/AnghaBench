#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_10__ {size_t len; int /*<<< orphan*/  crc; int /*<<< orphan*/  id; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_1__ header; int /*<<< orphan*/  value2; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ ngx_http_tfs_ns_ctl_request_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_header_t ;
struct TYPE_13__ {int /*<<< orphan*/ * next; TYPE_5__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_14__ {size_t last; scalar_t__ pos; } ;
typedef  TYPE_5__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_CLIENT_CMD_MESSAGE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_CLIENT_CMD_SET_PARAM ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_PACKET_VERSION ; 
 TYPE_4__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_crc (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ngx_http_tfs_generate_packet_id () ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_tfs_create_ctl_message(ngx_http_tfs_t *t, uint8_t cmd)
{
    size_t                          size;
    ngx_buf_t                      *b;
    ngx_chain_t                    *cl;
    ngx_http_tfs_ns_ctl_request_t  *req;

    size = sizeof(ngx_http_tfs_ns_ctl_request_t);

    b = ngx_create_temp_buf(t->pool, size);
    if (b == NULL) {
        return NULL;
    }

    req = (ngx_http_tfs_ns_ctl_request_t *) b->pos;
    req->header.type = NGX_HTTP_TFS_CLIENT_CMD_MESSAGE;
    req->header.len = size - sizeof(ngx_http_tfs_header_t);
    req->header.flag = NGX_HTTP_TFS_PACKET_FLAG;
    req->header.version = NGX_HTTP_TFS_PACKET_VERSION;
    req->header.id = ngx_http_tfs_generate_packet_id();
    req->cmd = NGX_HTTP_TFS_CLIENT_CMD_SET_PARAM;
    req->value2 = cmd;

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