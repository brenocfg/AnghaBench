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
typedef  struct TYPE_32__   TYPE_24__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_38__ {scalar_t__ code; int /*<<< orphan*/  msg; } ;
struct TYPE_39__ {int version; TYPE_7__ action; } ;
struct TYPE_36__ {int /*<<< orphan*/  tag; } ;
struct TYPE_40__ {scalar_t__ state; scalar_t__ length; scalar_t__ (* process_request_body ) (TYPE_9__*) ;TYPE_6__* main_conf; TYPE_10__* data; int /*<<< orphan*/  log; int /*<<< orphan*/  output_size; TYPE_8__ r_ctx; scalar_t__ parent; int /*<<< orphan*/ * busy_bufs; TYPE_5__ output; int /*<<< orphan*/  out_bufs; int /*<<< orphan*/  free_bufs; int /*<<< orphan*/  pool; TYPE_4__* tfs_peer; TYPE_2__* tfs_peer_servers; } ;
typedef  TYPE_9__ ngx_http_tfs_t ;
struct TYPE_27__ {TYPE_12__* connection; } ;
typedef  TYPE_10__ ngx_http_request_t ;
struct TYPE_28__ {int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  send_lowat; } ;
typedef  TYPE_11__ ngx_http_core_loc_conf_t ;
struct TYPE_29__ {scalar_t__ (* recv ) (TYPE_12__*,size_t,size_t) ;TYPE_24__* read; TYPE_24__* write; TYPE_10__* data; } ;
typedef  TYPE_12__ ngx_connection_t ;
struct TYPE_30__ {size_t end; size_t last; } ;
typedef  TYPE_13__ ngx_buf_t ;
struct TYPE_37__ {int /*<<< orphan*/  tfs_read_timeout; scalar_t__ body_buffer_size; } ;
struct TYPE_34__ {TYPE_12__* connection; } ;
struct TYPE_35__ {TYPE_3__ peer; TYPE_13__ body_buffer; } ;
struct TYPE_31__ {TYPE_12__* connection; } ;
struct TYPE_33__ {TYPE_1__ peer; TYPE_13__ body_buffer; } ;
struct TYPE_32__ {scalar_t__ timer_set; scalar_t__ ready; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_GET_APPID ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_READ_FILE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_STAT_FILE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 size_t NGX_HTTP_TFS_DATA_SERVER ; 
 scalar_t__ NGX_HTTP_TFS_STATE_ACTION_DONE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_READ_DONE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_STAT_DONE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_WRITE_DONE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_24__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_24__*) ; 
 scalar_t__ ngx_handle_write_event (TYPE_24__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_11__* ngx_http_get_module_loc_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_output_filter (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_clear_buf (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (TYPE_12__*,size_t,size_t) ; 
 scalar_t__ stub2 (TYPE_9__*) ; 

__attribute__((used)) static void
ngx_http_tfs_process_non_buffered_request(ngx_http_tfs_t *t,
    ngx_uint_t do_write)
{
    size_t                     size;
    ssize_t                    n;
    ngx_int_t                  rc, finalize_state;
    ngx_buf_t                 *b;
    ngx_connection_t          *downstream, *upstream;
    ngx_http_request_t        *r;
    ngx_http_core_loc_conf_t  *clcf;

    r = t->data;
    finalize_state = 0;
    rc = 0;
    b = NULL;
    downstream = r->connection;
    upstream = NULL;

    if (t->r_ctx.version == 1) {
        /* data server */
        b = &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER].body_buffer;
        upstream =t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER].peer.connection;

    } else if (t->r_ctx.action.code != NGX_HTTP_TFS_ACTION_GET_APPID) {
        b = &t->tfs_peer->body_buffer;
        upstream = t->tfs_peer->peer.connection;
    }

    for ( ;; ) {
        if (do_write) {

            if (t->out_bufs || t->busy_bufs) {

                rc = ngx_http_output_filter(r, t->out_bufs);

                if (rc == NGX_ERROR) {
                    ngx_http_tfs_finalize_request(r, t, 0);
                    return;
                }

#if defined(nginx_version) && (nginx_version > 1001003)
                ngx_chain_update_chains(t->pool, &t->free_bufs, &t->busy_bufs,
                                        &t->out_bufs, t->output.tag);
#else
                ngx_chain_update_chains(&t->free_bufs, &t->busy_bufs,
                                        &t->out_bufs, t->output.tag);
#endif
            }

            /* send all end */
            if (t->busy_bufs == NULL) {

                /* sub process */
                if (t->parent) {
                    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE
                        && t->state == NGX_HTTP_TFS_STATE_READ_DONE)
                    {
                        ngx_http_tfs_clear_buf(b);
                        ngx_http_tfs_finalize_request(r, t, NGX_DONE);
                        return;
                    }
                }

                t->output_size += t->main_conf->body_buffer_size;

                if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_GET_APPID
                    || (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE
                        && t->state == NGX_HTTP_TFS_STATE_READ_DONE)
                    || (t->r_ctx.version == 2
                        && t->state == NGX_HTTP_TFS_STATE_ACTION_DONE)
                    || (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_STAT_FILE
                        && t->state == NGX_HTTP_TFS_STATE_STAT_DONE)
                    || (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE
                        && t->state == NGX_HTTP_TFS_STATE_WRITE_DONE))
                {
                    /* need log size */
                    ngx_log_error(NGX_LOG_INFO, t->log, 0,
                                  "%V, output %uL byte",
                                  &t->r_ctx.action.msg, t->output_size);
                    ngx_http_tfs_finalize_request(r, t, 0);
                    return;
                }

                ngx_http_tfs_clear_buf(b);
            }
        }

        size = b->end - b->last;

        if (t->length > 0 && size && upstream->read->ready) {
            n = upstream->recv(upstream, b->last, size);

            if (n == NGX_AGAIN) {
                break;
            }

            if (n > 0) {
                b->last += n;
                do_write = 1;

                /* copy buf to out_bufs */
                rc = t->process_request_body(t);
                if (rc == NGX_ERROR) {
                    ngx_log_error(NGX_LOG_ERR, t->log, 0,
                                  "process request body failed");
                    ngx_http_tfs_finalize_request(t->data, t,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return;
                }

                /* ngx_ok or ngx_done */
                if (rc != NGX_AGAIN) {
                    finalize_state = 1;
                    break;
                }
            }

            continue;
        }

        break;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (downstream->data == r) {
        if (ngx_handle_write_event(downstream->write, clcf->send_lowat)
            != NGX_OK)
        {
            ngx_http_tfs_finalize_request(r, t, 0);
            return;
        }
    }

    if (downstream->write->active && !downstream->write->ready) {
        ngx_add_timer(downstream->write, clcf->send_timeout);

    } else if (downstream->write->timer_set) {
        ngx_del_timer(downstream->write);
    }

    if (t->length > 0 && upstream->read->active && !upstream->read->ready) {
        ngx_add_timer(upstream->read, t->main_conf->tfs_read_timeout);

    } else if (upstream->read->timer_set) {
        ngx_del_timer(upstream->read);
    }

    if (finalize_state) {
        ngx_http_tfs_finalize_state(t, rc);
    }
}