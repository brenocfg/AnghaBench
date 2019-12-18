#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_18__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_stream_upstream_t ;
typedef  int /*<<< orphan*/  ngx_stream_upstream_state_t ;
struct TYPE_33__ {TYPE_6__* upstream; TYPE_12__* connection; int /*<<< orphan*/ * captures_data; int /*<<< orphan*/ * captures; int /*<<< orphan*/  ncaptures; int /*<<< orphan*/ * log_handler; int /*<<< orphan*/ * variables; int /*<<< orphan*/ * upstream_states; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  health_check; int /*<<< orphan*/  stat_processing; scalar_t__ ssl; int /*<<< orphan*/  status; int /*<<< orphan*/  phase_handler; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; int /*<<< orphan*/  start_msec; int /*<<< orphan*/  start_sec; int /*<<< orphan*/  received; int /*<<< orphan*/  signature; } ;
typedef  TYPE_7__ ngx_stream_session_t ;
struct TYPE_34__ {TYPE_7__* session; TYPE_4__* conf; } ;
typedef  TYPE_8__ ngx_stream_multi_upstream_peer_data_t ;
struct TYPE_35__ {int used; int /*<<< orphan*/  queue; int /*<<< orphan*/  sockaddr; TYPE_4__* conf; int /*<<< orphan*/  socklen; TYPE_12__* connection; } ;
typedef  TYPE_9__ ngx_stream_multi_upstream_cache_t ;
struct TYPE_22__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_10__ ngx_peer_connection_t ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_11__ ngx_multi_connection_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_24__ {TYPE_18__* log; TYPE_3__* write; TYPE_2__* read; TYPE_17__* pool; TYPE_11__* multi_c; TYPE_7__* data; int /*<<< orphan*/  listening; } ;
typedef  TYPE_12__ ngx_connection_t ;
struct TYPE_31__ {TYPE_18__* log; int /*<<< orphan*/  name; TYPE_12__* connection; } ;
struct TYPE_32__ {int multi; TYPE_5__ peer; TYPE_1__* state; int /*<<< orphan*/ * resolved; int /*<<< orphan*/  upstream; int /*<<< orphan*/ * downstream_busy; int /*<<< orphan*/ * downstream_out; int /*<<< orphan*/ * upstream_busy; int /*<<< orphan*/ * upstream_out; int /*<<< orphan*/ * free; } ;
struct TYPE_30__ {int /*<<< orphan*/  cache; } ;
struct TYPE_29__ {TYPE_18__* log; } ;
struct TYPE_28__ {TYPE_18__* log; } ;
struct TYPE_27__ {int /*<<< orphan*/  peer; } ;
struct TYPE_26__ {TYPE_7__* data; } ;
struct TYPE_25__ {TYPE_18__* log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 TYPE_17__* ngx_create_pool (int,TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_18__* ngx_palloc (TYPE_17__*,int) ; 
 void* ngx_pcalloc (TYPE_17__*,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_stream_multi_upstream_add_data (TYPE_12__*,TYPE_7__*) ; 

ngx_int_t
ngx_stream_multi_upstream_init_connection(ngx_connection_t *c,
    ngx_peer_connection_t *pc, void *data)
{
    ngx_stream_multi_upstream_peer_data_t  *kp = data;
    ngx_stream_multi_upstream_cache_t      *item;
    ngx_multi_connection_t                 *multi_c;
    ngx_stream_session_t                   *fake_s, *s;

    c->pool = ngx_create_pool(128, kp->session->connection->log);
    if (c->pool == NULL) {
        return NGX_ERROR;
    }

    item = ngx_pcalloc(c->pool, sizeof(ngx_stream_multi_upstream_cache_t));
    if (item == NULL) {
        return NGX_ERROR;
    }

    item->connection = c;
    item->socklen    = pc->socklen;
    item->used       = 1;
    item->conf       = kp->conf;

    ngx_memcpy(&item->sockaddr, pc->sockaddr, pc->socklen);

    ngx_queue_insert_head(&kp->conf->cache, &item->queue);

    //init multi connection
    multi_c = ngx_pcalloc(c->pool, sizeof(ngx_multi_connection_t));
    if (multi_c == NULL) {
        return NGX_ERROR;
    }
    ngx_queue_init(&multi_c->data);

    fake_s = ngx_pcalloc(c->pool, sizeof(ngx_stream_session_t));
    if (fake_s == NULL) {
        return NGX_ERROR;
    }

    //init fake_s
#if 0
    *fake_s = *kp->session;
#endif
    s = kp->session;
    fake_s->signature = s->signature;
    fake_s->connection = c;  //just use backend pc fake
    c->listening = s->connection->listening;
    fake_s->received = s->received;
    fake_s->start_sec = s->start_sec;
    fake_s->start_msec = s->start_msec;
    fake_s->main_conf = s->main_conf;
    fake_s->srv_conf = s->srv_conf;
    fake_s->phase_handler = s->phase_handler;
    fake_s->status = s->status;

    fake_s->ssl = 0;
    fake_s->stat_processing = s->stat_processing;
    fake_s->health_check = s->health_check;

    fake_s->upstream = ngx_pcalloc(c->pool, sizeof(ngx_stream_upstream_t));
    if (fake_s->upstream == NULL) {
        return NGX_ERROR;
    }
#if 0
    *fake_s->upstream = *kp->session->upstream;
#endif
    fake_s->upstream->peer.connection = c;
    fake_s->upstream->peer.name = s->upstream->peer.name;
    fake_s->upstream->free = NULL;
    fake_s->upstream->upstream_out = NULL;
    fake_s->upstream->upstream_busy = NULL;
    fake_s->upstream->downstream_out = NULL;
    fake_s->upstream->downstream_busy = NULL;

    fake_s->upstream->upstream = s->upstream->upstream;
    fake_s->upstream->resolved = NULL;
    fake_s->upstream->state = ngx_pcalloc(c->pool, sizeof(ngx_stream_upstream_state_t));
    if (fake_s->upstream->state == NULL) {
        return NGX_ERROR;
    }
    fake_s->upstream->state->peer = fake_s->upstream->peer.name;
    fake_s->upstream->multi = 1;

    fake_s->ctx = NULL;
    fake_s->upstream_states = NULL;
    fake_s->variables = NULL;
    fake_s->log_handler = NULL;
#if (NGX_PCRE)
    fake_s->ncaptures = s->ncaptures;
    fake_s->captures = NULL;
    fake_s->captures_data = NULL;
#endif

    c->data = fake_s;
    c->multi_c = multi_c;

    c->log = ngx_palloc(c->pool, sizeof(ngx_log_t));
    if (c->log == NULL) {
        return NGX_ERROR;
    }
    *c->log = *kp->session->connection->log;
    c->log->data = fake_s;
    fake_s->upstream->peer.log = c->log;
    c->pool->log = c->log;

    c->read->log = c->log;
    c->write->log = c->log;

    return ngx_stream_multi_upstream_add_data(c, kp->session);
}