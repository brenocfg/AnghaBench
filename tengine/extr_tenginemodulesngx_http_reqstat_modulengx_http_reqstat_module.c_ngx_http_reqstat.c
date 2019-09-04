#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_2__ name; } ;
struct TYPE_22__ {TYPE_3__ shm; } ;
typedef  TYPE_5__ ngx_shm_zone_t ;
struct TYPE_23__ {TYPE_15__* monitor; } ;
typedef  TYPE_6__ ngx_http_reqstat_conf_t ;
struct TYPE_24__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_18__ {int nelts; TYPE_4__* elts; } ;
struct TYPE_17__ {size_t nelts; TYPE_5__** elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_15__* NGX_CONF_UNSET_PTR ; 
 void* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__** ngx_array_push (TYPE_15__*) ; 
 TYPE_6__* ngx_http_conf_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 TYPE_5__* ngx_shared_memory_add (TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_reqstat(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                    *value;
    ngx_uint_t                    i, j;
    ngx_shm_zone_t               *shm_zone, **z;
    ngx_http_reqstat_conf_t      *smcf;

    ngx_http_reqstat_conf_t      *rlcf = conf;

    value = cf->args->elts;
    smcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_reqstat_module);

    if (rlcf->monitor != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    if (smcf->monitor == NULL) {
        smcf->monitor = ngx_array_create(cf->pool, cf->args->nelts - 1,
                                         sizeof(ngx_shm_zone_t *));
        if (smcf->monitor == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    rlcf->monitor = ngx_array_create(cf->pool, cf->args->nelts - 1,
                                     sizeof(ngx_shm_zone_t *));
    if (rlcf->monitor == NULL) {
        return NGX_CONF_ERROR;
    }

    for (i = 1; i < cf->args->nelts; i++) {
        shm_zone = ngx_shared_memory_add(cf, &value[i], 0,
                                         &ngx_http_reqstat_module);
        if (shm_zone == NULL) {
            return NGX_CONF_ERROR;
        }

        z = ngx_array_push(rlcf->monitor);
        *z = shm_zone;

        z = smcf->monitor->elts;
        for (j = 0; j < smcf->monitor->nelts; j++) {
            if (!ngx_strcmp(value[i].data, z[j]->shm.name.data)) {
                break;
            }
        }

        if (j == smcf->monitor->nelts) {
            z = ngx_array_push(smcf->monitor);
            if (z == NULL) {
                return NGX_CONF_ERROR;
            }
            *z = shm_zone;
        }
    }

    return NGX_CONF_OK;
}