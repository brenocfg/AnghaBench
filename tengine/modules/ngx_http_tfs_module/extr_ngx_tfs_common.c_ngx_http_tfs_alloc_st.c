#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int segment_count; } ;
struct TYPE_18__ {int /*<<< orphan*/ * filter_ctx; } ;
struct TYPE_16__ {scalar_t__ code; } ;
struct TYPE_17__ {TYPE_3__ action; } ;
struct TYPE_21__ {int temporary; int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
struct TYPE_15__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_14__ {int /*<<< orphan*/ * start; } ;
struct TYPE_20__ {TYPE_6__ file; int /*<<< orphan*/  is_large_file; int /*<<< orphan*/  writer; TYPE_5__ output; int /*<<< orphan*/  pool; TYPE_4__ r_ctx; TYPE_8__ body_buffer; struct TYPE_20__* tfs_peer_servers; TYPE_2__ peer; TYPE_1__ header_buffer; int /*<<< orphan*/ * recv_chain; struct TYPE_20__* parent; struct TYPE_20__* next; struct TYPE_20__* free_sts; } ;
typedef  TYPE_7__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_peer_connection_t ;
typedef  TYPE_8__ ngx_buf_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_TFS_ACTION_READ_FILE ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_WRITE_FILE ; 
 size_t NGX_HTTP_TFS_DATA_SERVER ; 
 int NGX_HTTP_TFS_MAX_FRAGMENT_SIZE ; 
 size_t NGX_HTTP_TFS_NAME_SERVER ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_NO ; 
 int NGX_HTTP_TFS_SERVER_COUNT ; 
 int /*<<< orphan*/ * ngx_http_tfs_alloc_chains (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_7__*,TYPE_7__*,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_7__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_http_tfs_t *
ngx_http_tfs_alloc_st(ngx_http_tfs_t *t)
{
    ngx_buf_t       *b;
    ngx_http_tfs_t  *st;

    st = t->free_sts;

    if (st) {
        t->free_sts = st->next;
        return st;
    }

    st = ngx_palloc(t->pool, sizeof(ngx_http_tfs_t));
    if (st == NULL) {
        return NULL;
    }
    ngx_memcpy(st, t, sizeof(ngx_http_tfs_t));
    st->parent = t;

    /* each st should have independent send/recv buf/peer/out_bufs,
     * and we only care about data server and name server(retry need)
     */

    /* recv(from upstream servers) bufs */
    st->recv_chain = ngx_http_tfs_alloc_chains(t->pool, 2);
    if (st->recv_chain == NULL) {
        return NULL;
    }
    st->header_buffer.start = NULL;

    /* peers */
    st->tfs_peer_servers = ngx_pcalloc(t->pool,
        sizeof(ngx_http_tfs_peer_connection_t) * NGX_HTTP_TFS_SERVER_COUNT);
    if (st->tfs_peer_servers == NULL) {
        return NULL;
    }

    /* name server related */
    ngx_memcpy(&st->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER],
               &t->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER],
               sizeof(ngx_http_tfs_peer_connection_t));
    st->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER].body_buffer.start = NULL;
    st->tfs_peer_servers[NGX_HTTP_TFS_NAME_SERVER].peer.connection = NULL;

    /* data server related */
    ngx_memcpy(&st->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER],
               &t->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER],
               sizeof(ngx_http_tfs_peer_connection_t));
    b = &st->tfs_peer_servers[NGX_HTTP_TFS_DATA_SERVER].body_buffer;
    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
        b->start = NULL;

    } else if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_READ_FILE){
        /* alloc buf that can hold all segment's data,
         * so that ngx_http_tfs_process_buf_overflow would not happen
         */
        b->start = ngx_palloc(t->pool, NGX_HTTP_TFS_MAX_FRAGMENT_SIZE);
        if (b->start == NULL) {
            return NULL;
        }

        b->pos = b->start;
        b->last = b->start;
        b->end = b->start + NGX_HTTP_TFS_MAX_FRAGMENT_SIZE;
        b->temporary = 1;
    }

    st->output.filter_ctx = &st->writer;

    st->is_large_file = NGX_HTTP_TFS_NO;
    st->file.segment_count = 1;

    return st;
}