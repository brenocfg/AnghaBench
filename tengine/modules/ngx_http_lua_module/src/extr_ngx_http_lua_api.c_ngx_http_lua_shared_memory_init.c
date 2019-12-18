#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ (* init ) (TYPE_2__*,void*) ;int /*<<< orphan*/  noreuse; int /*<<< orphan*/  shm; void* data; } ;
typedef  TYPE_2__ ngx_shm_zone_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; int /*<<< orphan*/ * cycle; TYPE_4__* lmcf; TYPE_2__ zone; } ;
typedef  TYPE_3__ ngx_http_lua_shm_zone_ctx_t ;
struct TYPE_11__ {scalar_t__ shm_zones_inited; scalar_t__ (* init_handler ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lua; TYPE_1__* shm_zones; } ;
typedef  TYPE_4__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  volatile* ngx_cycle ; 
 int /*<<< orphan*/  ngx_test_config ; 
 scalar_t__ stub1 (TYPE_2__*,void*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_shared_memory_init(ngx_shm_zone_t *shm_zone, void *data)
{
    ngx_http_lua_shm_zone_ctx_t *octx = data;
    ngx_shm_zone_t              *ozone;
    void                        *odata;

    ngx_int_t                    rc;
    volatile ngx_cycle_t        *saved_cycle;
    ngx_http_lua_main_conf_t    *lmcf;
    ngx_http_lua_shm_zone_ctx_t *ctx;
    ngx_shm_zone_t              *zone;

    ctx = (ngx_http_lua_shm_zone_ctx_t *) shm_zone->data;
    zone = &ctx->zone;

    odata = NULL;
    if (octx) {
        ozone = &octx->zone;
        odata = ozone->data;
    }

    zone->shm = shm_zone->shm;
#if defined(nginx_version) && nginx_version >= 1009000
    zone->noreuse = shm_zone->noreuse;
#endif

    if (zone->init(zone, odata) != NGX_OK) {
        return NGX_ERROR;
    }

    dd("get lmcf");

    lmcf = ctx->lmcf;
    if (lmcf == NULL) {
        return NGX_ERROR;
    }

    dd("lmcf->lua: %p", lmcf->lua);

    lmcf->shm_zones_inited++;

    if (lmcf->shm_zones_inited == lmcf->shm_zones->nelts
        && lmcf->init_handler && !ngx_test_config)
    {
        saved_cycle = ngx_cycle;
        ngx_cycle = ctx->cycle;

        rc = lmcf->init_handler(ctx->log, lmcf, lmcf->lua);

        ngx_cycle = saved_cycle;

        if (rc != NGX_OK) {
            /* an error happened */
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}