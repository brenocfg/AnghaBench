#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {size_t last_number; int init_number; int vnumber; TYPE_5__* last_peer; TYPE_3__* vpeers; } ;
typedef  TYPE_1__ ngx_http_upstream_vnswrr_srv_conf_t ;
struct TYPE_16__ {uintptr_t* tried; TYPE_5__* current; TYPE_4__* peers; } ;
struct TYPE_12__ {TYPE_1__* uvnscf; TYPE_6__ rrp; } ;
typedef  TYPE_2__ ngx_http_upstream_vnswrr_peer_data_t ;
struct TYPE_13__ {int rindex; TYPE_5__* vpeer; } ;
typedef  TYPE_3__ ngx_http_upstream_rr_vpeers_t ;
struct TYPE_14__ {int number; int total_weight; scalar_t__ weighted; TYPE_5__* peer; } ;
typedef  TYPE_4__ ngx_http_upstream_rr_peers_t ;
struct TYPE_15__ {scalar_t__ max_fails; scalar_t__ fails; scalar_t__ checked; scalar_t__ fail_timeout; scalar_t__ max_conns; scalar_t__ conns; int /*<<< orphan*/  check_index; scalar_t__ down; struct TYPE_15__* next; } ;
typedef  TYPE_5__ ngx_http_upstream_rr_peer_t ;
typedef  TYPE_6__ ngx_http_upstream_rr_peer_data_t ;

/* Variables and functions */
 size_t NGX_CONF_UNSET_UINT ; 
 scalar_t__ ngx_http_upstream_check_peer_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_init_virtual_peers (TYPE_4__*,TYPE_1__*,size_t,size_t) ; 
 int ngx_random () ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_http_upstream_rr_peer_t *
ngx_http_upstream_get_vnswrr(ngx_http_upstream_vnswrr_peer_data_t  *vnsp)
{
    time_t                                  now;
    uintptr_t                               m;
    ngx_uint_t                              i, n, p, flag, begin_number;
    ngx_http_upstream_rr_peer_t            *peer, *best;
    ngx_http_upstream_rr_peers_t           *peers;
    ngx_http_upstream_rr_vpeers_t          *vpeers;
    ngx_http_upstream_rr_peer_data_t       *rrp;
    ngx_http_upstream_vnswrr_srv_conf_t    *uvnscf;

    now = ngx_time();

    best = NULL;

#if (NGX_SUPPRESS_WARN)
    p = 0;
#endif

    rrp = &vnsp->rrp;
    peers = rrp->peers;
    uvnscf = vnsp->uvnscf;
    vpeers = uvnscf->vpeers;

    if (uvnscf->last_number == NGX_CONF_UNSET_UINT) {
        uvnscf->init_number = ngx_random() % peers->number;

        if (peers->weighted) {
            peer = vpeers[uvnscf->init_number].vpeer;

        } else {
            for (peer = peers->peer, i = 0; i < uvnscf->init_number; i++) {
                peer = peer->next;
            }
        }

        uvnscf->last_number = uvnscf->init_number;
        uvnscf->last_peer = peer;
    }

    if (peers->weighted) {
        /* batch initialization vpeers at runtime. */
        if (uvnscf->vnumber != peers->total_weight
            && (uvnscf->last_number + 1 == uvnscf->vnumber))
        {
            n = peers->total_weight - uvnscf->vnumber;
            if (n > peers->number) {
                n = peers->number;
            }

            ngx_http_upstream_init_virtual_peers(peers, uvnscf, uvnscf->vnumber,
			                         n + uvnscf->vnumber);

        }

        begin_number = (uvnscf->last_number + 1) % uvnscf->vnumber;
        peer = vpeers[begin_number].vpeer;

    } else {
        if (uvnscf->last_peer && uvnscf->last_peer->next) {
            begin_number = (uvnscf->last_number + 1) % peers->number;
            peer = uvnscf->last_peer->next;

        } else {
            begin_number = 0;
            peer = peers->peer;
        }
    }

    for (i = begin_number, flag = 1; i != begin_number || flag;
         i = peers->weighted
         ? ((i + 1) % uvnscf->vnumber) : ((i + 1) % peers->number),
         peer = peers->weighted
         ? vpeers[i].vpeer : (peer->next ? peer->next : peers->peer))
    {

        flag = 0;
        if (peers->weighted) {

            n = peers->total_weight - uvnscf->vnumber;
            if (n > peers->number) {
                n = peers->number;
            }

            ngx_http_upstream_init_virtual_peers(peers, uvnscf, uvnscf->vnumber,
			                         n + uvnscf->vnumber);

            n = vpeers[i].rindex / (8 * sizeof(uintptr_t));
            m = (uintptr_t) 1 << vpeers[i].rindex % (8 * sizeof(uintptr_t));

        } else {
            n =  i / (8 * sizeof(uintptr_t));
            m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));
        }

        if (rrp->tried[n] & m) {
            continue;
        }

        if (peer->down) {
            continue;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            continue;
        }

#if defined(nginx_version) && nginx_version >= 1011005
        if (peer->max_conns && peer->conns >= peer->max_conns) {
            continue;
        }
#endif

#if (NGX_HTTP_UPSTREAM_CHECK)
        if (ngx_http_upstream_check_peer_down(peer->check_index)) {
            continue;
        }
#endif

        best = peer;
        uvnscf->last_peer = peer;
        uvnscf->last_number = i;
        p = i;
        break;
    }

    if (best == NULL) {
        return NULL;
    }

    rrp->current = best;

    if (peers->weighted) {
        n = vpeers[p].rindex / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << vpeers[p].rindex % (8 * sizeof(uintptr_t));

    } else {
        n = p / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));
    }

    rrp->tried[n] |= m;

    if (now - best->checked > best->fail_timeout) {
        best->checked = now;
    }

    return best;
}