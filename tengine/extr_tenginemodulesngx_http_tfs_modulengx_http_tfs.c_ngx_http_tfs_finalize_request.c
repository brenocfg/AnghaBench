#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_26__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_28__ {TYPE_26__* connection; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_11__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_41__ {scalar_t__ code; } ;
struct TYPE_42__ {TYPE_8__ action; } ;
struct TYPE_40__ {TYPE_6__* segment_data; } ;
struct TYPE_36__ {scalar_t__ size; } ;
struct TYPE_29__ {scalar_t__ sp_curr; size_t tfs_peer_count; scalar_t__ json_output; int /*<<< orphan*/  (* finalize_request ) (TYPE_12__*) ;TYPE_9__ r_ctx; int /*<<< orphan*/  (* sp_callback ) (TYPE_12__*) ;TYPE_19__* log; TYPE_16__* parent; TYPE_7__ file; TYPE_3__ stat_info; struct TYPE_29__* next; TYPE_1__* tfs_peer_servers; void* sp_ready; int /*<<< orphan*/  sp_fail_count; } ;
typedef  TYPE_12__ ngx_http_tfs_t ;
struct TYPE_30__ {TYPE_10__* connection; int /*<<< orphan*/  write_event_handler; } ;
typedef  TYPE_13__ ngx_http_request_t ;
struct TYPE_38__ {scalar_t__ size; } ;
struct TYPE_39__ {TYPE_5__ segment_info; } ;
struct TYPE_37__ {int /*<<< orphan*/  left_length; } ;
struct TYPE_35__ {int /*<<< orphan*/  size; } ;
struct TYPE_34__ {scalar_t__ fd; scalar_t__ pool; } ;
struct TYPE_33__ {TYPE_11__ peer; } ;
struct TYPE_32__ {char* action; } ;
struct TYPE_31__ {scalar_t__ sp_curr; scalar_t__ sp_done_count; scalar_t__ sp_count; int /*<<< orphan*/  (* sp_callback ) (TYPE_16__*) ;void* request_timeout; int /*<<< orphan*/  sp_fail_count; TYPE_4__ file; TYPE_2__ stat_info; int /*<<< orphan*/  sp_succ_count; } ;
struct TYPE_27__ {TYPE_19__* log; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_LAST ; 
 scalar_t__ NGX_HTTP_REQUEST_TIME_OUT ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_KEEPALIVE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_READ_FILE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 void* NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_26__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_13__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_request_empty_handler ; 
 scalar_t__ ngx_http_send_special (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_free_st (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_json_destroy (scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_19__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,TYPE_19__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_16__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_12__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_12__*) ; 

void
ngx_http_tfs_finalize_request(ngx_http_request_t *r, ngx_http_tfs_t *t,
    ngx_int_t rc)
{
    ngx_uint_t              i;
    ngx_http_tfs_t         *next_st;
    ngx_peer_connection_t  *p;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "finalize http tfs request: %i", rc);

    if (t->parent
        && t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE
        && t->parent->sp_curr != t->sp_curr)
    {
        if (rc != NGX_DONE) {
            t->sp_fail_count++;
        }
        /* output in the right turn */
        t->sp_ready = NGX_HTTP_TFS_YES;
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, t->log, 0,
                       "curr output segment is [%uD], [%uD] is ready, wait for call...",
                       t->parent->sp_curr, t->sp_curr);
        return;
    }

    for (i = 0; i < t->tfs_peer_count; i++) {
        p = &t->tfs_peer_servers[i].peer;
        if (p->free) {
            p->free(p, p->data, 0);
        }

        if (p->connection) {
            if (p->free) {
                p->free(p, p->data, 0);
            }

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "close http upstream connection: %d",
                           p->connection->fd);

            if (p->connection->pool) {
                ngx_destroy_pool(p->connection->pool);
            }

            ngx_close_connection(p->connection);
        }

        p->connection = NULL;
    }
#if (NGX_DEBUG)
    ngx_http_connection_pool_check(t->main_conf->conn_pool, t->log);
#endif

    /* sub process return here */
    if (t->parent) {
        /* free st for reuse */
        next_st = t->next;
        ngx_http_tfs_free_st(t);

        r->write_event_handler = ngx_http_request_empty_handler;

        if (rc == NGX_DONE) {
            t->parent->sp_succ_count++;
            t->parent->stat_info.size += t->stat_info.size;
            if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
                t->parent->file.left_length -=
                                        t->file.segment_data->segment_info.size;
            }

        } else {
            t->parent->sp_fail_count++;
            if (rc == NGX_HTTP_REQUEST_TIME_OUT) {
                t->parent->request_timeout = NGX_HTTP_TFS_YES;
            }
        }
        t->parent->sp_done_count++;
        t->parent->sp_curr++;
        /* all sub process done, wake up parent process */
        if (t->parent->sp_done_count == t->parent->sp_count){
            t->parent->sp_callback(t->parent);

        } else {
            if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE) {
                /* wake up next sub process */
                ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                               "segment[%uD] output complete, call next...",
                               t->sp_curr);
                if (next_st) {
                    next_st->sp_callback(next_st);
                }
            }
        }

        return;
    }

    /* rc-keepalive */
    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_KEEPALIVE) {
        t->finalize_request(t);
        return;
    }

    if (t->json_output) {
        ngx_http_tfs_json_destroy(t->json_output);
    }

    r->connection->log->action = "sending to client";
    if (rc == NGX_OK) {
        rc = ngx_http_send_special(r, NGX_HTTP_LAST);
    }

    ngx_http_finalize_request(r, rc);
}