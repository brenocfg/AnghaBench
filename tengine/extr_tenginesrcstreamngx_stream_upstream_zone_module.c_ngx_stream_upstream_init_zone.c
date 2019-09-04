#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {TYPE_5__* data; } ;
struct TYPE_19__ {TYPE_8__* shm_zone; TYPE_1__ peer; } ;
typedef  TYPE_4__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_20__ {struct TYPE_20__* zone_next; } ;
typedef  TYPE_5__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_18__ {size_t nelts; TYPE_4__** elts; } ;
struct TYPE_21__ {TYPE_3__ upstreams; } ;
typedef  TYPE_6__ ngx_stream_upstream_main_conf_t ;
struct TYPE_22__ {TYPE_5__* data; int /*<<< orphan*/ * log_ctx; } ;
typedef  TYPE_7__ ngx_slab_pool_t ;
struct TYPE_15__ {size_t len; } ;
struct TYPE_17__ {TYPE_13__ name; scalar_t__ exists; scalar_t__ addr; } ;
struct TYPE_23__ {TYPE_2__ shm; TYPE_6__* data; } ;
typedef  TYPE_8__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_slab_alloc (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,TYPE_13__*) ; 
 TYPE_5__* ngx_stream_upstream_zone_copy_peers (TYPE_7__*,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_upstream_init_zone(ngx_shm_zone_t *shm_zone, void *data)
{
    size_t                            len;
    ngx_uint_t                        i;
    ngx_slab_pool_t                  *shpool;
    ngx_stream_upstream_rr_peers_t   *peers, **peersp;
    ngx_stream_upstream_srv_conf_t   *uscf, **uscfp;
    ngx_stream_upstream_main_conf_t  *umcf;

    shpool = (ngx_slab_pool_t *) shm_zone->shm.addr;
    umcf = shm_zone->data;
    uscfp = umcf->upstreams.elts;

    if (shm_zone->shm.exists) {
        peers = shpool->data;

        for (i = 0; i < umcf->upstreams.nelts; i++) {
            uscf = uscfp[i];

            if (uscf->shm_zone != shm_zone) {
                continue;
            }

            uscf->peer.data = peers;
            peers = peers->zone_next;
        }

        return NGX_OK;
    }

    len = sizeof(" in upstream zone \"\"") + shm_zone->shm.name.len;

    shpool->log_ctx = ngx_slab_alloc(shpool, len);
    if (shpool->log_ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_sprintf(shpool->log_ctx, " in upstream zone \"%V\"%Z",
                &shm_zone->shm.name);


    /* copy peers to shared memory */

    peersp = (ngx_stream_upstream_rr_peers_t **) (void *) &shpool->data;

    for (i = 0; i < umcf->upstreams.nelts; i++) {
        uscf = uscfp[i];

        if (uscf->shm_zone != shm_zone) {
            continue;
        }

        peers = ngx_stream_upstream_zone_copy_peers(shpool, uscf);
        if (peers == NULL) {
            return NGX_ERROR;
        }

        *peersp = peers;
        peersp = &peers->zone_next;
    }

    return NGX_OK;
}