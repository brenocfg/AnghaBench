#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_shm_zone_t ;
struct TYPE_10__ {int /*<<< orphan*/ * display; } ;
typedef  TYPE_2__ ngx_http_reqstat_conf_t ;
struct TYPE_11__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_12__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_9__ {int nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_http_conf_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 int /*<<< orphan*/  ngx_http_reqstat_show_handler ; 
 int /*<<< orphan*/ * ngx_shared_memory_add (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_reqstat_show(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                    *value;
    ngx_uint_t                    i;
    ngx_shm_zone_t               *shm_zone, **z;
    ngx_http_core_loc_conf_t     *clcf;

    ngx_http_reqstat_conf_t      *rlcf = conf;

    value = cf->args->elts;

    if (rlcf->display != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    if (cf->args->nelts == 1) {
        rlcf->display = NULL;
        goto reg_handler;
    }

    rlcf->display = ngx_array_create(cf->pool, cf->args->nelts - 1,
                                     sizeof(ngx_shm_zone_t *));
    if (rlcf->display == NULL) {
        return NGX_CONF_ERROR;
    }

    for (i = 1; i < cf->args->nelts; i++) {
        shm_zone = ngx_shared_memory_add(cf, &value[i], 0,
                                         &ngx_http_reqstat_module);
        if (shm_zone == NULL) {
            return NGX_CONF_ERROR;
        }

        z = ngx_array_push(rlcf->display);
        *z = shm_zone;
    }

reg_handler:

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_reqstat_show_handler;

    return NGX_CONF_OK;
}