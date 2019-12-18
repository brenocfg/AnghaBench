#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int isold; int isinit; } ;
typedef  TYPE_2__ ngx_http_lua_fake_shm_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_fake_shm_init_zone(ngx_shm_zone_t *shm_zone, void *data)
{
    ngx_http_lua_fake_shm_ctx_t  *octx = data;

    ngx_http_lua_fake_shm_ctx_t  *ctx;

    ctx = shm_zone->data;

    if (octx) {
        ctx->isold = 1;
    }

    ctx->isinit = 1;

    return NGX_OK;
}