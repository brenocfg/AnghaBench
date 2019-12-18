#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {int state; int /*<<< orphan*/ * tfs_peer_servers; int /*<<< orphan*/  pool; TYPE_2__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_1__ ngx_http_tfs_t ;
struct TYPE_9__ {int /*<<< orphan*/  body_buffer; } ;
typedef  TYPE_2__ ngx_http_tfs_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_10__ {scalar_t__ len; } ;
typedef  TYPE_3__ ngx_http_tfs_header_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 size_t NGX_HTTP_TFS_META_SERVER ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_peer_set_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_root_server_parse_message (TYPE_1__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_select_meta_server (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_set_custom_initial_parameters (TYPE_1__*) ; 

ngx_int_t
ngx_http_tfs_process_rs(ngx_http_tfs_t *t)
{
    ngx_int_t                        rc;
    ngx_buf_t                       *b;
    ngx_http_tfs_inet_t             *addr;
    ngx_http_tfs_header_t           *header;
    ngx_http_tfs_peer_connection_t  *tp;

    header = (ngx_http_tfs_header_t *) t->header;
    tp = t->tfs_peer;
    b = &tp->body_buffer;

    if (ngx_buf_size(b) < header->len) {
        return NGX_AGAIN;
    }

    rc = ngx_http_tfs_root_server_parse_message(t);
    if (rc != NGX_OK) {
        return rc;
    }

    t->state += 1;

    ngx_http_tfs_set_custom_initial_parameters(t);

    addr = ngx_http_tfs_select_meta_server(t);
    ngx_http_tfs_peer_set_addr(t->pool,
                               &t->tfs_peer_servers[NGX_HTTP_TFS_META_SERVER],
                               addr);

    return NGX_OK;
}