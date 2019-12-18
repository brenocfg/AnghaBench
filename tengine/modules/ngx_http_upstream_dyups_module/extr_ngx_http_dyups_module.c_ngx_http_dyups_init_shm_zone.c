#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_slab_pool_t ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_1__ shm; } ;
typedef  TYPE_2__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/ * status; scalar_t__ version; int /*<<< orphan*/  msg_queue; } ;
typedef  TYPE_3__ ngx_dyups_shctx_t ;
struct TYPE_10__ {int /*<<< orphan*/ * shpool; TYPE_3__* sh; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__ ngx_dyups_global_ctx ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_slab_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dyups_init_shm_zone(ngx_shm_zone_t *shm_zone, void *data)
{
    ngx_slab_pool_t    *shpool;
    ngx_dyups_shctx_t  *sh;

    shpool = (ngx_slab_pool_t *) shm_zone->shm.addr;

    sh = ngx_slab_alloc(shpool, sizeof(ngx_dyups_shctx_t));
    if (sh == NULL) {
        return NGX_ERROR;
    }

    ngx_dyups_global_ctx.sh = sh;
    ngx_dyups_global_ctx.shpool = shpool;

    ngx_queue_init(&sh->msg_queue);

    sh->version = 0;
    sh->status = NULL;

    return NGX_OK;
}