#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {scalar_t__ max_fails; scalar_t__ fails; scalar_t__ checked; scalar_t__ fail_timeout; scalar_t__ max_conns; scalar_t__ conns; scalar_t__ current_weight; scalar_t__ effective_weight; scalar_t__ weight; scalar_t__ down; struct TYPE_7__* next; } ;
typedef  TYPE_2__ ngx_http_upstream_rr_peer_t ;
struct TYPE_8__ {uintptr_t* tried; TYPE_2__* current; TYPE_1__* peers; } ;
typedef  TYPE_3__ ngx_http_upstream_rr_peer_data_t ;
struct TYPE_6__ {TYPE_2__* peer; } ;

/* Variables and functions */
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_http_upstream_rr_peer_t *
ngx_http_upstream_get_peer(ngx_http_upstream_rr_peer_data_t *rrp)
{
    time_t                        now;
    uintptr_t                     m;
#if (T_NGX_HTTP_UPSTREAM_RANDOM)
    ngx_int_t                     total, flag;
#else
    ngx_int_t                     total;
#endif
    ngx_uint_t                    i, n, p;
    ngx_http_upstream_rr_peer_t  *peer, *best;

    now = ngx_time();

    best = NULL;
    total = 0;

#if (NGX_SUPPRESS_WARN)
    p = 0;
#endif

#if (T_NGX_HTTP_UPSTREAM_RANDOM)
    if (rrp->peers->init_number == NGX_CONF_UNSET_UINT) {
         rrp->peers->init_number = ngx_random() % rrp->peers->number;
    }

    for (peer = rrp->peers->peer, i = 0; i < rrp->peers->init_number; i++) {
        peer = peer->next;
    }

    flag = 1;
    for (i = rrp->peers->init_number;
         i != rrp->peers->init_number || flag;
         i = (i + 1) % rrp->peers->number,
         peer = peer->next ? peer->next : rrp->peers->peer)
    {
        flag = 0;

#else
    for (peer = rrp->peers->peer, i = 0;
         peer;
         peer = peer->next, i++)
    {
#endif
        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            continue;
        }

        if (peer->down) {
            continue;
        }

#if (NGX_HTTP_UPSTREAM_CHECK)
        if (ngx_http_upstream_check_peer_down(peer->check_index)) {
            continue;
        }
#endif

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            continue;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            continue;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }
    }

    if (best == NULL) {
        return NULL;
    }

    rrp->current = best;

    n = p / (8 * sizeof(uintptr_t));
    m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));

    rrp->tried[n] |= m;

    best->current_weight -= total;

    if (now - best->checked > best->fail_timeout) {
        best->checked = now;
    }

    return best;
}