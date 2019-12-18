#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_20__ {int single; int number; TYPE_7__* peer; int /*<<< orphan*/ * name; } ;
typedef  TYPE_6__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_19__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_21__ {int socklen; int weight; int effective_weight; int max_fails; int fail_timeout; struct TYPE_21__* next; scalar_t__ max_conns; scalar_t__ current_weight; TYPE_5__ name; struct sockaddr* sockaddr; } ;
typedef  TYPE_7__ ngx_stream_upstream_rr_peer_t ;
struct TYPE_22__ {TYPE_6__* peers; scalar_t__* tried; scalar_t__ data; scalar_t__ config; int /*<<< orphan*/ * current; } ;
typedef  TYPE_8__ ngx_stream_upstream_rr_peer_data_t ;
struct TYPE_23__ {int naddrs; int socklen; int /*<<< orphan*/  port; TYPE_3__* addrs; TYPE_5__ name; struct sockaddr* sockaddr; int /*<<< orphan*/  host; } ;
typedef  TYPE_9__ ngx_stream_upstream_resolved_t ;
struct TYPE_14__ {TYPE_2__* upstream; TYPE_4__* connection; } ;
typedef  TYPE_10__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;
struct TYPE_17__ {int socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_15__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  tries; int /*<<< orphan*/  free; int /*<<< orphan*/  get; TYPE_8__* data; } ;
struct TYPE_16__ {TYPE_1__ peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_inet_set_port (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_sock_ntop (struct sockaddr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_stream_upstream_empty_save_session ; 
 int /*<<< orphan*/  ngx_stream_upstream_empty_set_session ; 
 int /*<<< orphan*/  ngx_stream_upstream_free_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_get_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_tries (TYPE_6__*) ; 

ngx_int_t
ngx_stream_upstream_create_round_robin_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_resolved_t *ur)
{
    u_char                              *p;
    size_t                               len;
    socklen_t                            socklen;
    ngx_uint_t                           i, n;
    struct sockaddr                     *sockaddr;
    ngx_stream_upstream_rr_peer_t       *peer, **peerp;
    ngx_stream_upstream_rr_peers_t      *peers;
    ngx_stream_upstream_rr_peer_data_t  *rrp;

    rrp = s->upstream->peer.data;

    if (rrp == NULL) {
        rrp = ngx_palloc(s->connection->pool,
                         sizeof(ngx_stream_upstream_rr_peer_data_t));
        if (rrp == NULL) {
            return NGX_ERROR;
        }

        s->upstream->peer.data = rrp;
    }

    peers = ngx_pcalloc(s->connection->pool,
                        sizeof(ngx_stream_upstream_rr_peers_t));
    if (peers == NULL) {
        return NGX_ERROR;
    }

    peer = ngx_pcalloc(s->connection->pool,
                       sizeof(ngx_stream_upstream_rr_peer_t) * ur->naddrs);
    if (peer == NULL) {
        return NGX_ERROR;
    }

    peers->single = (ur->naddrs == 1);
    peers->number = ur->naddrs;
    peers->name = &ur->host;

    if (ur->sockaddr) {
        peer[0].sockaddr = ur->sockaddr;
        peer[0].socklen = ur->socklen;
        peer[0].name = ur->name;
        peer[0].weight = 1;
        peer[0].effective_weight = 1;
        peer[0].current_weight = 0;
        peer[0].max_conns = 0;
        peer[0].max_fails = 1;
        peer[0].fail_timeout = 10;
        peers->peer = peer;

    } else {
        peerp = &peers->peer;

        for (i = 0; i < ur->naddrs; i++) {

            socklen = ur->addrs[i].socklen;

            sockaddr = ngx_palloc(s->connection->pool, socklen);
            if (sockaddr == NULL) {
                return NGX_ERROR;
            }

            ngx_memcpy(sockaddr, ur->addrs[i].sockaddr, socklen);
            ngx_inet_set_port(sockaddr, ur->port);

            p = ngx_pnalloc(s->connection->pool, NGX_SOCKADDR_STRLEN);
            if (p == NULL) {
                return NGX_ERROR;
            }

            len = ngx_sock_ntop(sockaddr, socklen, p, NGX_SOCKADDR_STRLEN, 1);

            peer[i].sockaddr = sockaddr;
            peer[i].socklen = socklen;
            peer[i].name.len = len;
            peer[i].name.data = p;
            peer[i].weight = 1;
            peer[i].effective_weight = 1;
            peer[i].current_weight = 0;
            peer[i].max_conns = 0;
            peer[i].max_fails = 1;
            peer[i].fail_timeout = 10;
            *peerp = &peer[i];
            peerp = &peer[i].next;
        }
    }

    rrp->peers = peers;
    rrp->current = NULL;
    rrp->config = 0;

    if (rrp->peers->number <= 8 * sizeof(uintptr_t)) {
        rrp->tried = &rrp->data;
        rrp->data = 0;

    } else {
        n = (rrp->peers->number + (8 * sizeof(uintptr_t) - 1))
                / (8 * sizeof(uintptr_t));

        rrp->tried = ngx_pcalloc(s->connection->pool, n * sizeof(uintptr_t));
        if (rrp->tried == NULL) {
            return NGX_ERROR;
        }
    }

    s->upstream->peer.get = ngx_stream_upstream_get_round_robin_peer;
    s->upstream->peer.free = ngx_stream_upstream_free_round_robin_peer;
    s->upstream->peer.tries = ngx_stream_upstream_tries(rrp->peers);
#if (NGX_STREAM_SSL)
    s->upstream->peer.set_session = ngx_stream_upstream_empty_set_session;
    s->upstream->peer.save_session = ngx_stream_upstream_empty_save_session;
#endif

    return NGX_OK;
}