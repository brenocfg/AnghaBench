#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_37__ {int code; } ;
struct TYPE_31__ {int version; TYPE_6__ action; } ;
struct TYPE_33__ {int /*<<< orphan*/ * tair_instance; TYPE_9__* data; } ;
struct TYPE_34__ {int /*<<< orphan*/  curr_lookup_cache; TYPE_2__ remote_ctx; int /*<<< orphan*/  use_cache; int /*<<< orphan*/ * local_ctx; } ;
struct TYPE_32__ {scalar_t__ tag; } ;
struct TYPE_40__ {TYPE_19__ r_ctx; TYPE_11__* loc_conf; int /*<<< orphan*/  header_only; TYPE_3__ block_cache_ctx; TYPE_1__ output; TYPE_10__* main_conf; int /*<<< orphan*/ * srv_conf; int /*<<< orphan*/  log; TYPE_12__* data; int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_srv_conf_t ;
struct TYPE_28__ {scalar_t__ enable_remote_block_cache; int /*<<< orphan*/  remote_block_cache_instance; int /*<<< orphan*/ * local_block_cache_ctx; } ;
typedef  TYPE_10__ ngx_http_tfs_main_conf_t ;
struct TYPE_29__ {TYPE_4__* upstream; } ;
typedef  TYPE_11__ ngx_http_tfs_loc_conf_t ;
struct TYPE_39__ {int content_length_n; } ;
struct TYPE_30__ {TYPE_8__ headers_out; TYPE_7__* main; TYPE_5__* connection; int /*<<< orphan*/  header_only; int /*<<< orphan*/  pool; } ;
typedef  TYPE_12__ ngx_http_request_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_38__ {int /*<<< orphan*/  count; } ;
struct TYPE_36__ {int /*<<< orphan*/  log; } ;
struct TYPE_35__ {int /*<<< orphan*/  enable_rcs; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_BAD_REQUEST ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
#define  NGX_HTTP_TFS_ACTION_CREATE_DIR 140 
#define  NGX_HTTP_TFS_ACTION_CREATE_FILE 139 
#define  NGX_HTTP_TFS_ACTION_GET_APPID 138 
#define  NGX_HTTP_TFS_ACTION_KEEPALIVE 137 
#define  NGX_HTTP_TFS_ACTION_LS_DIR 136 
#define  NGX_HTTP_TFS_ACTION_LS_FILE 135 
#define  NGX_HTTP_TFS_ACTION_MOVE_DIR 134 
#define  NGX_HTTP_TFS_ACTION_MOVE_FILE 133 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 132 
#define  NGX_HTTP_TFS_ACTION_REMOVE_DIR 131 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 130 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 129 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 128 
 int /*<<< orphan*/  NGX_HTTP_TFS_LOCAL_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_REMOTE_BLOCK_CACHE ; 
 scalar_t__ NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_discard_request_body (TYPE_12__*) ; 
 TYPE_11__* ngx_http_get_module_loc_conf (TYPE_12__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_http_get_module_main_conf (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_get_module_srv_conf (TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_read_client_request_body (TYPE_12__*,int /*<<< orphan*/  (*) (TYPE_12__*)) ; 
 scalar_t__ ngx_http_restful_parse (TYPE_12__*,TYPE_19__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_12__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_module ; 
 int /*<<< orphan*/  ngx_http_tfs_read_body_handler (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_handler(ngx_http_request_t *r)
{
    ngx_int_t                  rc;
    ngx_http_tfs_t            *t;
    ngx_http_tfs_loc_conf_t   *tlcf;
    ngx_http_tfs_srv_conf_t   *tscf;
    ngx_http_tfs_main_conf_t  *tmcf;

    tlcf = ngx_http_get_module_loc_conf(r, ngx_http_tfs_module);
    tscf = ngx_http_get_module_srv_conf(r, ngx_http_tfs_module);
    tmcf = ngx_http_get_module_main_conf(r, ngx_http_tfs_module);

    t = ngx_pcalloc(r->pool, sizeof(ngx_http_tfs_t));

    if (t == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "alloc ngx_http_tfs_t failed");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    t->pool = r->pool;
    t->data = r;
    t->log = r->connection->log;
    t->loc_conf = tlcf;
    t->srv_conf = tscf;
    t->main_conf = tmcf;
    t->output.tag = (ngx_buf_tag_t) &ngx_http_tfs_module;
    if (tmcf->local_block_cache_ctx != NULL) {
        t->block_cache_ctx.use_cache |= NGX_HTTP_TFS_LOCAL_BLOCK_CACHE;
        t->block_cache_ctx.local_ctx = tmcf->local_block_cache_ctx;
    }
    if (tmcf->enable_remote_block_cache == NGX_HTTP_TFS_YES) {
        t->block_cache_ctx.use_cache |= NGX_HTTP_TFS_REMOTE_BLOCK_CACHE;
    }
    t->block_cache_ctx.remote_ctx.data = t;
    t->block_cache_ctx.remote_ctx.tair_instance =
                                             &tmcf->remote_block_cache_instance;
    t->block_cache_ctx.curr_lookup_cache = NGX_HTTP_TFS_LOCAL_BLOCK_CACHE;

    rc = ngx_http_restful_parse(r, &t->r_ctx);
    if (rc != NGX_OK) {
        return rc;
    }

    t->header_only = r->header_only;

    if (!t->loc_conf->upstream->enable_rcs && t->r_ctx.version == 2) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "custom file requires tfs_enable_rcs on,"
                      " and make sure you have MetaServer and RootServer!");
        return NGX_HTTP_BAD_REQUEST;
    }

    switch (t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_CREATE_DIR:
    case NGX_HTTP_TFS_ACTION_CREATE_FILE:
    case NGX_HTTP_TFS_ACTION_REMOVE_DIR:
    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
    case NGX_HTTP_TFS_ACTION_MOVE_DIR:
    case NGX_HTTP_TFS_ACTION_MOVE_FILE:
    case NGX_HTTP_TFS_ACTION_LS_DIR:
    case NGX_HTTP_TFS_ACTION_LS_FILE:
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
    case NGX_HTTP_TFS_ACTION_KEEPALIVE:
    case NGX_HTTP_TFS_ACTION_READ_FILE:
    case NGX_HTTP_TFS_ACTION_GET_APPID:
        rc = ngx_http_discard_request_body(r);

        if (rc != NGX_OK) {
            return rc;
        }

        r->headers_out.content_length_n = -1;
        ngx_http_set_ctx(r, t, ngx_http_tfs_module);
        r->main->count++;
        ngx_http_tfs_read_body_handler(r);
        break;
    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        r->headers_out.content_length_n = -1;
        ngx_http_set_ctx(r, t, ngx_http_tfs_module);
        rc = ngx_http_read_client_request_body(r,
                                               ngx_http_tfs_read_body_handler);
        if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }
        break;
    }

    return NGX_DONE;
}