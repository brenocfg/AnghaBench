#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_16__ {TYPE_9__* shm_zone; } ;
typedef  TYPE_2__ ngx_stream_upstream_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_stream_upstream_main_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_18__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_19__ {int noreuse; int /*<<< orphan*/ * data; int /*<<< orphan*/  init; } ;
struct TYPE_15__ {int nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int ngx_pagesize ; 
 scalar_t__ ngx_parse_size (TYPE_3__*) ; 
 TYPE_9__* ngx_shared_memory_add (TYPE_4__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_stream_conf_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_stream_conf_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_upstream_init_zone ; 
 int /*<<< orphan*/  ngx_stream_upstream_module ; 

__attribute__((used)) static char *
ngx_stream_upstream_zone(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ssize_t                           size;
    ngx_str_t                        *value;
    ngx_stream_upstream_srv_conf_t   *uscf;
    ngx_stream_upstream_main_conf_t  *umcf;

    uscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_upstream_module);
    umcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_upstream_module);

    value = cf->args->elts;

    if (!value[1].len) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid zone name \"%V\"", &value[1]);
        return NGX_CONF_ERROR;
    }

    if (cf->args->nelts == 3) {
        size = ngx_parse_size(&value[2]);

        if (size == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid zone size \"%V\"", &value[2]);
            return NGX_CONF_ERROR;
        }

        if (size < (ssize_t) (8 * ngx_pagesize)) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "zone \"%V\" is too small", &value[1]);
            return NGX_CONF_ERROR;
        }

    } else {
        size = 0;
    }

    uscf->shm_zone = ngx_shared_memory_add(cf, &value[1], size,
                                           &ngx_stream_upstream_module);
    if (uscf->shm_zone == NULL) {
        return NGX_CONF_ERROR;
    }

    uscf->shm_zone->init = ngx_stream_upstream_init_zone;
    uscf->shm_zone->data = umcf;

    uscf->shm_zone->noreuse = 1;

    return NGX_CONF_OK;
}