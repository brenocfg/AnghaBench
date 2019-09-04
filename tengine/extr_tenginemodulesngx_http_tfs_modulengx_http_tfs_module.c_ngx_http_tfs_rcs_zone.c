#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_15__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  init; } ;
typedef  TYPE_3__ ngx_shm_zone_t ;
struct TYPE_16__ {TYPE_2__ rcs_zone_name; int /*<<< orphan*/ * rc_ctx; } ;
typedef  TYPE_4__ ngx_http_tfs_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_rc_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
struct TYPE_13__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_http_tfs_module ; 
 int /*<<< orphan*/  ngx_http_tfs_rc_server_init_zone ; 
 int ngx_pagesize ; 
 scalar_t__ ngx_parse_size (TYPE_2__*) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_shared_memory_add (TYPE_5__*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_tfs_rcs_zone(ngx_conf_t *cf, ngx_http_tfs_upstream_t *tu)
{
    ssize_t                 size;
    ngx_str_t              *value, s, name;
    ngx_uint_t              i;
    ngx_shm_zone_t         *shm_zone;
    ngx_http_tfs_rc_ctx_t  *ctx;

    value = cf->args->elts;
    size = 0;
    name.len = 0;

    if (cf->args->nelts != 3) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid number of arguments in "
                           "\"rcs_zone\" directive");
        return NGX_CONF_ERROR;
    }

    for (i = 1; i < cf->args->nelts; i++) {

        if (ngx_strncmp(value[i].data, "size=", 5) == 0) {
            s.len = value[i].len - 5;
            s.data = value[i].data + 5;

            size = ngx_parse_size(&s);

            if (size == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid zone size \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            if (size < (ssize_t) (8 * ngx_pagesize)) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "zone \"%V\" is too small", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "name=", 5) == 0) {
            name.len = value[i].len - 5;
            name.data = value[i].data + 5;

            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[i]);
        return NGX_CONF_ERROR;
    }


    if (size == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"rcs_zone\" must have \"size\" parameter");
        return NGX_CONF_ERROR;
    }

    if (name.len == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"rcs_zone\" must have  \"name\" parameter");
        return NGX_CONF_ERROR;
    }

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_http_tfs_rc_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    shm_zone = ngx_shared_memory_add(cf, &name, size,
                                     &ngx_http_tfs_module);
    if (shm_zone == NULL) {
        return NGX_CONF_ERROR;
    }

    shm_zone->init = ngx_http_tfs_rc_server_init_zone;
    shm_zone->data = ctx;

    tu->rc_ctx = ctx;
    tu->rcs_zone_name = name;

    return NGX_CONF_OK;
}