#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_21__ {scalar_t__ single; } ;
typedef  TYPE_3__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_22__ {scalar_t__ max_fails; scalar_t__ fails; scalar_t__ checked; scalar_t__ fail_timeout; scalar_t__ max_conns; scalar_t__ conns; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; scalar_t__ down; } ;
typedef  TYPE_4__ ngx_stream_upstream_rr_peer_t ;
struct TYPE_23__ {uintptr_t* tried; TYPE_4__* current; TYPE_3__* peers; } ;
typedef  TYPE_5__ ngx_stream_upstream_rr_peer_data_t ;
struct TYPE_24__ {int tries; TYPE_2__* conf; TYPE_5__ rrp; } ;
typedef  TYPE_6__ ngx_stream_upstream_random_peer_data_t ;
struct TYPE_25__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/ * connection; scalar_t__ cached; int /*<<< orphan*/  tries; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_20__ {TYPE_1__* ranges; } ;
struct TYPE_19__ {TYPE_4__* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_upstream_get_round_robin_peer (TYPE_7__*,TYPE_5__*) ; 
 size_t ngx_stream_upstream_peek_random_peer (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peer_lock (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peer_unlock (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peers_rlock (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peers_unlock (TYPE_3__*) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_stream_upstream_get_random_peer(ngx_peer_connection_t *pc, void *data)
{
    ngx_stream_upstream_random_peer_data_t  *rp = data;

    time_t                               now;
    uintptr_t                            m;
    ngx_uint_t                           i, n;
    ngx_stream_upstream_rr_peer_t       *peer;
    ngx_stream_upstream_rr_peers_t      *peers;
    ngx_stream_upstream_rr_peer_data_t  *rrp;

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, pc->log, 0,
                   "get random peer, try: %ui", pc->tries);

    rrp = &rp->rrp;
    peers = rrp->peers;

    ngx_stream_upstream_rr_peers_rlock(peers);

    if (rp->tries > 20 || peers->single) {
        ngx_stream_upstream_rr_peers_unlock(peers);
        return ngx_stream_upstream_get_round_robin_peer(pc, rrp);
    }

    pc->cached = 0;
    pc->connection = NULL;

    now = ngx_time();

    for ( ;; ) {

        i = ngx_stream_upstream_peek_random_peer(peers, rp);

        peer = rp->conf->ranges[i].peer;

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next;
        }

        ngx_stream_upstream_rr_peer_lock(peers, peer);

        if (peer->down) {
            ngx_stream_upstream_rr_peer_unlock(peers, peer);
            goto next;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            ngx_stream_upstream_rr_peer_unlock(peers, peer);
            goto next;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            ngx_stream_upstream_rr_peer_unlock(peers, peer);
            goto next;
        }

        break;

    next:

        if (++rp->tries > 20) {
            ngx_stream_upstream_rr_peers_unlock(peers);
            return ngx_stream_upstream_get_round_robin_peer(pc, rrp);
        }
    }

    rrp->current = peer;

    if (now - peer->checked > peer->fail_timeout) {
        peer->checked = now;
    }

    pc->sockaddr = peer->sockaddr;
    pc->socklen = peer->socklen;
    pc->name = &peer->name;

    peer->conns++;

    ngx_stream_upstream_rr_peer_unlock(peers, peer);
    ngx_stream_upstream_rr_peers_unlock(peers);

    rrp->tried[n] |= m;

    return NGX_OK;
}