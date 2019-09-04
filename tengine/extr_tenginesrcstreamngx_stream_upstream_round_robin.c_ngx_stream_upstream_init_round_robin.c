#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ port; size_t naddrs; TYPE_3__* addrs; int /*<<< orphan*/  err; int /*<<< orphan*/  host; } ;
typedef  TYPE_5__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {TYPE_8__* data; int /*<<< orphan*/  init; } ;
struct TYPE_21__ {scalar_t__ port; TYPE_4__ peer; int /*<<< orphan*/  host; int /*<<< orphan*/  line; int /*<<< orphan*/  file_name; TYPE_1__* servers; } ;
typedef  TYPE_6__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_22__ {size_t naddrs; size_t weight; int max_fails; int fail_timeout; int /*<<< orphan*/  name; int /*<<< orphan*/  down; scalar_t__ max_conns; TYPE_2__* addrs; scalar_t__ backup; } ;
typedef  TYPE_7__ ngx_stream_upstream_server_t ;
struct TYPE_23__ {int single; size_t number; int weighted; size_t total_weight; TYPE_9__* peer; int /*<<< orphan*/ * name; struct TYPE_23__* next; } ;
typedef  TYPE_8__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_24__ {size_t weight; size_t effective_weight; int max_fails; int fail_timeout; struct TYPE_24__* next; scalar_t__ max_conns; scalar_t__ current_weight; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  server; int /*<<< orphan*/  down; } ;
typedef  TYPE_9__ ngx_stream_upstream_rr_peer_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_16__ {size_t nelts; TYPE_7__* elts; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_inet_resolve_host (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_stream_upstream_init_round_robin_peer ; 

ngx_int_t
ngx_stream_upstream_init_round_robin(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{
    ngx_url_t                        u;
    ngx_uint_t                       i, j, n, w;
    ngx_stream_upstream_server_t    *server;
    ngx_stream_upstream_rr_peer_t   *peer, **peerp;
    ngx_stream_upstream_rr_peers_t  *peers, *backup;

    us->peer.init = ngx_stream_upstream_init_round_robin_peer;

    if (us->servers) {
        server = us->servers->elts;

        n = 0;
        w = 0;

        for (i = 0; i < us->servers->nelts; i++) {
            if (server[i].backup) {
                continue;
            }

            n += server[i].naddrs;
            w += server[i].naddrs * server[i].weight;
        }

        if (n == 0) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no servers in upstream \"%V\" in %s:%ui",
                          &us->host, us->file_name, us->line);
            return NGX_ERROR;
        }

        peers = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peers_t));
        if (peers == NULL) {
            return NGX_ERROR;
        }

        peer = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peer_t) * n);
        if (peer == NULL) {
            return NGX_ERROR;
        }

        peers->single = (n == 1);
        peers->number = n;
        peers->weighted = (w != n);
        peers->total_weight = w;
        peers->name = &us->host;

        n = 0;
        peerp = &peers->peer;

        for (i = 0; i < us->servers->nelts; i++) {
            if (server[i].backup) {
                continue;
            }

            for (j = 0; j < server[i].naddrs; j++) {
                peer[n].sockaddr = server[i].addrs[j].sockaddr;
                peer[n].socklen = server[i].addrs[j].socklen;
                peer[n].name = server[i].addrs[j].name;
                peer[n].weight = server[i].weight;
                peer[n].effective_weight = server[i].weight;
                peer[n].current_weight = 0;
                peer[n].max_conns = server[i].max_conns;
                peer[n].max_fails = server[i].max_fails;
                peer[n].fail_timeout = server[i].fail_timeout;
                peer[n].down = server[i].down;
                peer[n].server = server[i].name;

                *peerp = &peer[n];
                peerp = &peer[n].next;
                n++;
            }
        }

        us->peer.data = peers;

        /* backup servers */

        n = 0;
        w = 0;

        for (i = 0; i < us->servers->nelts; i++) {
            if (!server[i].backup) {
                continue;
            }

            n += server[i].naddrs;
            w += server[i].naddrs * server[i].weight;
        }

        if (n == 0) {
            return NGX_OK;
        }

        backup = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peers_t));
        if (backup == NULL) {
            return NGX_ERROR;
        }

        peer = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peer_t) * n);
        if (peer == NULL) {
            return NGX_ERROR;
        }

        peers->single = 0;
        backup->single = 0;
        backup->number = n;
        backup->weighted = (w != n);
        backup->total_weight = w;
        backup->name = &us->host;

        n = 0;
        peerp = &backup->peer;

        for (i = 0; i < us->servers->nelts; i++) {
            if (!server[i].backup) {
                continue;
            }

            for (j = 0; j < server[i].naddrs; j++) {
                peer[n].sockaddr = server[i].addrs[j].sockaddr;
                peer[n].socklen = server[i].addrs[j].socklen;
                peer[n].name = server[i].addrs[j].name;
                peer[n].weight = server[i].weight;
                peer[n].effective_weight = server[i].weight;
                peer[n].current_weight = 0;
                peer[n].max_conns = server[i].max_conns;
                peer[n].max_fails = server[i].max_fails;
                peer[n].fail_timeout = server[i].fail_timeout;
                peer[n].down = server[i].down;
                peer[n].server = server[i].name;

                *peerp = &peer[n];
                peerp = &peer[n].next;
                n++;
            }
        }

        peers->next = backup;

        return NGX_OK;
    }


    /* an upstream implicitly defined by proxy_pass, etc. */

    if (us->port == 0) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no port in upstream \"%V\" in %s:%ui",
                      &us->host, us->file_name, us->line);
        return NGX_ERROR;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.host = us->host;
    u.port = us->port;

    if (ngx_inet_resolve_host(cf->pool, &u) != NGX_OK) {
        if (u.err) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "%s in upstream \"%V\" in %s:%ui",
                          u.err, &us->host, us->file_name, us->line);
        }

        return NGX_ERROR;
    }

    n = u.naddrs;

    peers = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peers_t));
    if (peers == NULL) {
        return NGX_ERROR;
    }

    peer = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_rr_peer_t) * n);
    if (peer == NULL) {
        return NGX_ERROR;
    }

    peers->single = (n == 1);
    peers->number = n;
    peers->weighted = 0;
    peers->total_weight = n;
    peers->name = &us->host;

    peerp = &peers->peer;

    for (i = 0; i < u.naddrs; i++) {
        peer[i].sockaddr = u.addrs[i].sockaddr;
        peer[i].socklen = u.addrs[i].socklen;
        peer[i].name = u.addrs[i].name;
        peer[i].weight = 1;
        peer[i].effective_weight = 1;
        peer[i].current_weight = 0;
        peer[i].max_conns = 0;
        peer[i].max_fails = 1;
        peer[i].fail_timeout = 10;
        *peerp = &peer[i];
        peerp = &peer[i].next;
    }

    us->peer.data = peers;

    /* implicitly defined upstream has no backup servers */

    return NGX_OK;
}