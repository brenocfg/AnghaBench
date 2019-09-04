#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  init; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_shm_zone_t ;
struct TYPE_8__ {int /*<<< orphan*/  shm_size; int /*<<< orphan*/  shm_name; } ;
typedef  TYPE_2__ ngx_http_dyups_main_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_dyups_get_shm_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_dyups_init_shm_zone ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 
 int /*<<< orphan*/  ngx_http_dyups_shm_generation ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_shared_memory_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_dyups_init_shm(ngx_conf_t *cf, void *conf)
{
    ngx_http_dyups_main_conf_t *dmcf = conf;

    ngx_shm_zone_t  *shm_zone;

    ngx_http_dyups_shm_generation++;

    if (ngx_http_dyups_get_shm_name(&dmcf->shm_name, cf->pool,
                                     ngx_http_dyups_shm_generation)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    shm_zone = ngx_shared_memory_add(cf, &dmcf->shm_name, dmcf->shm_size,
                                     &ngx_http_dyups_module);
    if (shm_zone == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0,
                  "[dyups] init shm:%V, size:%ui", &dmcf->shm_name,
                  dmcf->shm_size);

    shm_zone->data = cf->pool;
    shm_zone->init = ngx_http_dyups_init_shm_zone;

    return NGX_CONF_OK;
}