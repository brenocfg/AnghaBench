#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_21__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_slab_pool_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; scalar_t__ addr; } ;
struct TYPE_28__ {TYPE_2__ shm; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_shm_zone_t ;
struct TYPE_29__ {int number; scalar_t__ checksum; int generation; int max_number; TYPE_9__* peers; } ;
typedef  TYPE_4__ ngx_pool_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_30__ {int /*<<< orphan*/  default_down; } ;
typedef  TYPE_5__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_24__ {int nelts; TYPE_8__* elts; } ;
struct TYPE_31__ {scalar_t__ checksum; TYPE_4__* peers_shm; int /*<<< orphan*/ * shpool; TYPE_1__ peers; } ;
typedef  TYPE_6__ ngx_http_upstream_check_peers_t ;
typedef  TYPE_4__ ngx_http_upstream_check_peers_shm_t ;
struct TYPE_32__ {TYPE_21__* peer_addr; TYPE_5__* conf; } ;
typedef  TYPE_8__ ngx_http_upstream_check_peer_t ;
struct TYPE_33__ {size_t socklen; int /*<<< orphan*/ * sockaddr; } ;
typedef  TYPE_9__ ngx_http_upstream_check_peer_shm_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_26__ {TYPE_4__* pool; } ;
struct TYPE_25__ {size_t socklen; int /*<<< orphan*/  name; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 int MAX_DYNAMIC_PEER ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* check_peers_ctx ; 
 TYPE_22__* ngx_cycle ; 
 TYPE_9__* ngx_http_upstream_check_find_shm_peer (TYPE_4__*,TYPE_21__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_get_shm_name (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ ngx_http_upstream_check_init_shm_peer (TYPE_9__*,TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 
 int ngx_http_upstream_check_shm_generation ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,size_t) ; 
 TYPE_3__* ngx_shared_memory_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ngx_slab_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_init_shm_zone(ngx_shm_zone_t *shm_zone, void *data)
{
    size_t                               size;
    ngx_str_t                            oshm_name;
    ngx_int_t                            rc;
    ngx_uint_t                           i, same, number;
    ngx_pool_t                          *pool;
    ngx_shm_zone_t                      *oshm_zone;
    ngx_slab_pool_t                     *shpool;
    ngx_http_upstream_check_peer_t      *peer;
    ngx_http_upstream_check_peers_t     *peers;
    ngx_http_upstream_check_srv_conf_t  *ucscf;
    ngx_http_upstream_check_peer_shm_t  *peer_shm, *opeer_shm;
    ngx_http_upstream_check_peers_shm_t *peers_shm, *opeers_shm;

    opeers_shm = NULL;
    peers_shm = NULL;
    ngx_str_set(&oshm_name, "");

    same = 0;
    peers = check_peers_ctx;
    if (peers == NULL) {
        return NGX_OK;
    }

    number = peers->peers.nelts;

    pool = shm_zone->data;
    if (pool == NULL) {
        pool = ngx_cycle->pool;
    }

    shpool = (ngx_slab_pool_t *) shm_zone->shm.addr;

    if (data) {
        opeers_shm = data;

        if ((opeers_shm->number == number)
            && (opeers_shm->checksum == peers->checksum)) {

            peers_shm = data;
            same = 1;
        }
    }

    if (!same) {

        if (ngx_http_upstream_check_shm_generation > 1) {

            ngx_http_upstream_check_get_shm_name(&oshm_name,
                    pool, ngx_http_upstream_check_shm_generation - 1);

            /* The global variable ngx_cycle still points to the old one */
            oshm_zone = ngx_shared_memory_find((ngx_cycle_t *) ngx_cycle,
                                               &oshm_name,
                                               &ngx_http_upstream_check_module);

            if (oshm_zone) {
                opeers_shm = oshm_zone->data;

                ngx_log_debug2(NGX_LOG_DEBUG_HTTP, shm_zone->shm.log, 0,
                               "http upstream check, find oshm_zone:%p, "
                               "opeers_shm: %p",
                               oshm_zone, opeers_shm);
            }
        }

        size = sizeof(*peers_shm) +
               (number - 1 + MAX_DYNAMIC_PEER) * sizeof(ngx_http_upstream_check_peer_shm_t);

        peers_shm = ngx_slab_alloc(shpool, size);

        if (peers_shm == NULL) {
            goto failure;
        }

        ngx_memzero(peers_shm, size);
    }

    peers_shm->generation = ngx_http_upstream_check_shm_generation;
    peers_shm->checksum = peers->checksum;
    peers_shm->number = number;
    peers_shm->max_number = number + MAX_DYNAMIC_PEER;

    peer = peers->peers.elts;

    for (i = 0; i < number; i++) {

        peer_shm = &peers_shm->peers[i];

        if (same) {
            continue;
        }

        peer_shm->socklen = peer[i].peer_addr->socklen;
        peer_shm->sockaddr = ngx_slab_alloc(shpool, peer_shm->socklen);
        if (peer_shm->sockaddr == NULL) {
            goto failure;
        }

        ngx_memcpy(peer_shm->sockaddr, peer[i].peer_addr->sockaddr,
                   peer_shm->socklen);

        if (opeers_shm) {

            opeer_shm = ngx_http_upstream_check_find_shm_peer(opeers_shm,
                                                             peer[i].peer_addr);
            if (opeer_shm) {
                ngx_log_debug1(NGX_LOG_DEBUG_HTTP, shm_zone->shm.log, 0,
                               "http upstream check, inherit opeer: %V ",
                               &peer[i].peer_addr->name);

                rc = ngx_http_upstream_check_init_shm_peer(peer_shm, opeer_shm,
                         0, pool, &peer[i].peer_addr->name);
                if (rc != NGX_OK) {
                    return NGX_ERROR;
                }

                continue;
            }
        }

        ucscf = peer[i].conf;
        rc = ngx_http_upstream_check_init_shm_peer(peer_shm, NULL,
                                                   ucscf->default_down, pool,
                                                   &peer[i].peer_addr->name);
        if (rc != NGX_OK) {
            return NGX_ERROR;
        }
    }

    peers->shpool = shpool;
    peers->peers_shm = peers_shm;
    shm_zone->data = peers_shm;

    return NGX_OK;

failure:
    ngx_log_error(NGX_LOG_EMERG, shm_zone->shm.log, 0,
                  "http upstream check_shm_size is too small, "
                  "you should specify a larger size.");
    return NGX_ERROR;
}