#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_1__ ngx_http_upstream_check_peer_shm_t ;
struct TYPE_5__ {int /*<<< orphan*/  shpool; } ;

/* Variables and functions */
 TYPE_3__* check_peers_ctx ; 
 int /*<<< orphan*/  ngx_slab_free_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_upstream_check_clear_dynamic_peer_shm(
    ngx_http_upstream_check_peer_shm_t *peer_shm)
{
    if (check_peers_ctx == NULL) {
        return;
    }

    ngx_slab_free_locked(check_peers_ctx->shpool, peer_shm->sockaddr);
}