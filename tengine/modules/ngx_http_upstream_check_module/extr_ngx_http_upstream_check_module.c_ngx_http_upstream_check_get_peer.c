#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {TYPE_2__* shm; } ;
typedef  TYPE_3__ ngx_http_upstream_check_peer_t ;
struct TYPE_6__ {TYPE_3__* elts; } ;
struct TYPE_9__ {TYPE_1__ peers; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  access_count; int /*<<< orphan*/  busyness; } ;

/* Variables and functions */
 TYPE_4__* check_peers_ctx ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ upstream_check_index_invalid (TYPE_4__*,size_t) ; 

void
ngx_http_upstream_check_get_peer(ngx_uint_t index)
{
    ngx_http_upstream_check_peer_t  *peer;

    if (upstream_check_index_invalid(check_peers_ctx, index)) {
        return;
    }

    peer = check_peers_ctx->peers.elts;

    ngx_shmtx_lock(&peer[index].shm->mutex);

    peer[index].shm->busyness++;
    peer[index].shm->access_count++;

    ngx_shmtx_unlock(&peer[index].shm->mutex);
}