#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_6__ {size_t down; } ;
typedef  TYPE_2__ ngx_http_upstream_check_peer_shm_t ;
struct TYPE_7__ {TYPE_1__* peers_shm; } ;
struct TYPE_5__ {TYPE_2__* peers; } ;

/* Variables and functions */
 TYPE_3__* check_peers_ctx ; 
 scalar_t__ upstream_check_index_invalid (TYPE_3__*,size_t) ; 

ngx_uint_t
ngx_http_upstream_check_peer_down(ngx_uint_t index)
{
    ngx_http_upstream_check_peer_shm_t   *peer_shm;

    if (upstream_check_index_invalid(check_peers_ctx, index)) {
        return 0;
    }

    peer_shm = check_peers_ctx->peers_shm->peers;

    return (peer_shm[index].down);
}