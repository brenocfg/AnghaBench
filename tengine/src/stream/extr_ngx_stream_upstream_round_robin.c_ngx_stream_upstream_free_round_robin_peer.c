#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* time_t ;
typedef  int ngx_uint_t ;
struct TYPE_12__ {int fails; scalar_t__ accessed; scalar_t__ checked; int max_fails; int effective_weight; int weight; int /*<<< orphan*/  conns; } ;
typedef  TYPE_1__ ngx_stream_upstream_rr_peer_t ;
struct TYPE_13__ {TYPE_4__* peers; TYPE_1__* current; } ;
typedef  TYPE_2__ ngx_stream_upstream_rr_peer_data_t ;
struct TYPE_14__ {TYPE_1__* tries; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
struct TYPE_15__ {scalar_t__ single; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int NGX_PEER_FAILED ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peer_lock (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peer_unlock (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peers_rlock (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_stream_upstream_rr_peers_unlock (TYPE_4__*) ; 
 void* ngx_time () ; 

void
ngx_stream_upstream_free_round_robin_peer(ngx_peer_connection_t *pc, void *data,
    ngx_uint_t state)
{
    ngx_stream_upstream_rr_peer_data_t  *rrp = data;

    time_t                          now;
    ngx_stream_upstream_rr_peer_t  *peer;

    ngx_log_debug2(NGX_LOG_DEBUG_STREAM, pc->log, 0,
                   "free rr peer %ui %ui", pc->tries, state);

    peer = rrp->current;

    ngx_stream_upstream_rr_peers_rlock(rrp->peers);
    ngx_stream_upstream_rr_peer_lock(rrp->peers, peer);

    if (rrp->peers->single) {
        peer->conns--;

        ngx_stream_upstream_rr_peer_unlock(rrp->peers, peer);
        ngx_stream_upstream_rr_peers_unlock(rrp->peers);

        pc->tries = 0;
        return;
    }

    if (state & NGX_PEER_FAILED) {
        now = ngx_time();

        peer->fails++;
        peer->accessed = now;
        peer->checked = now;

        if (peer->max_fails) {
            peer->effective_weight -= peer->weight / peer->max_fails;

            if (peer->fails >= peer->max_fails) {
                ngx_log_error(NGX_LOG_WARN, pc->log, 0,
                              "upstream server temporarily disabled");
            }
        }

        ngx_log_debug2(NGX_LOG_DEBUG_STREAM, pc->log, 0,
                       "free rr peer failed: %p %i",
                       peer, peer->effective_weight);

        if (peer->effective_weight < 0) {
            peer->effective_weight = 0;
        }

    } else {

        /* mark peer live if check passed */

        if (peer->accessed < peer->checked) {
            peer->fails = 0;
        }
    }

    peer->conns--;

    ngx_stream_upstream_rr_peer_unlock(rrp->peers, peer);
    ngx_stream_upstream_rr_peers_unlock(rrp->peers);

    if (pc->tries) {
        pc->tries--;
    }
}