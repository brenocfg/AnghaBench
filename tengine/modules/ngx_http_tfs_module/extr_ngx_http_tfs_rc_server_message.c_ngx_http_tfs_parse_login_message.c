#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {int /*<<< orphan*/  appkey; } ;
struct TYPE_22__ {TYPE_6__* rc_info_node; int /*<<< orphan*/  log; TYPE_3__ r_ctx; TYPE_2__* loc_conf; TYPE_8__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
struct TYPE_23__ {int /*<<< orphan*/  session_id; int /*<<< orphan*/  app_id; } ;
typedef  TYPE_6__ ngx_http_tfs_rcs_info_t ;
struct TYPE_24__ {TYPE_4__* shpool; } ;
typedef  TYPE_7__ ngx_http_tfs_rc_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/  pos; } ;
struct TYPE_25__ {TYPE_10__ body_buffer; } ;
typedef  TYPE_8__ ngx_http_tfs_peer_connection_t ;
struct TYPE_26__ {int type; } ;
typedef  TYPE_9__ ngx_http_tfs_header_t ;
struct TYPE_21__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_19__ {TYPE_1__* upstream; } ;
struct TYPE_18__ {TYPE_7__* rc_ctx; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_create_info_node (TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_dump_rc_info (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_tfs_parse_session_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* ngx_http_tfs_rcs_lookup (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_tfs_status_message (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

ngx_int_t
ngx_http_tfs_parse_login_message(ngx_http_tfs_t *t)
{
    uint16_t                         type;
    ngx_str_t                        err_msg;
    ngx_int_t                        rc;
    ngx_http_tfs_header_t           *header;
    ngx_http_tfs_rc_ctx_t           *rc_ctx;
    ngx_http_tfs_rcs_info_t         *rc_info;
    ngx_http_tfs_peer_connection_t  *tp;

    header = (ngx_http_tfs_header_t *) t->header;
    tp = t->tfs_peer;
    type = header->type;
    rc_ctx = t->loc_conf->upstream->rc_ctx;

    switch (type) {
    case NGX_HTTP_TFS_STATUS_MESSAGE:
        ngx_str_set(&err_msg, "login rc");
        return ngx_http_tfs_status_message(&tp->body_buffer, &err_msg, t->log);
    }

    ngx_shmtx_lock(&rc_ctx->shpool->mutex);
    rc_info = ngx_http_tfs_rcs_lookup(rc_ctx, t->r_ctx.appkey);

    rc = NGX_OK;

    if (rc_info == NULL) {
        rc = ngx_http_tfs_create_info_node(t, rc_ctx, tp->body_buffer.pos,
                                           t->r_ctx.appkey);

    } else {
        t->rc_info_node = rc_info;
    }
    ngx_shmtx_unlock(&rc_ctx->shpool->mutex);

#if (NGX_DEBUG)
    ngx_http_tfs_dump_rc_info(t->rc_info_node, t->log);
#endif

    if (rc == NGX_OK) {
        rc = ngx_http_tfs_parse_session_id(&t->rc_info_node->session_id,
                                           &t->rc_info_node->app_id);
        if (rc == NGX_ERROR) {
            ngx_log_error(NGX_LOG_ERR, t->log, 0,
                          "invalid session id: %V",
                          &t->rc_info_node->session_id);
        }
    }
    return rc;
}