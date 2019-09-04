#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_17__ {double load; scalar_t__ mode; double cpuusage; double swap; int free; double rt; TYPE_1__* rt_ring; int /*<<< orphan*/  log_level; int /*<<< orphan*/  rt_action; int /*<<< orphan*/  interval; int /*<<< orphan*/  free_action; int /*<<< orphan*/  swap_action; int /*<<< orphan*/  cpuusage_action; int /*<<< orphan*/  load_action; int /*<<< orphan*/  enable; } ;
typedef  TYPE_4__ ngx_http_sysguard_conf_t ;
struct TYPE_18__ {TYPE_3__* connection; int /*<<< orphan*/  uri; TYPE_2__* main; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {int sysguard_set; } ;
struct TYPE_14__ {scalar_t__ cached_rt_exptime; double cached_rt; } ;

/* Variables and functions */
 double NGX_CONF_UNSET ; 
 int NGX_CONF_UNSET_SIZE ; 
 int NGX_DECLINED ; 
 scalar_t__ NGX_HTTP_SYSGUARD_MODE_AND ; 
 scalar_t__ NGX_HTTP_SYSGUARD_MODE_OR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 double ngx_http_sysguard_cached_cpuusage ; 
 scalar_t__ ngx_http_sysguard_cached_cpuusage_exptime ; 
 int ngx_http_sysguard_cached_free ; 
 double ngx_http_sysguard_cached_load ; 
 scalar_t__ ngx_http_sysguard_cached_load_exptime ; 
 scalar_t__ ngx_http_sysguard_cached_mem_exptime ; 
 double ngx_http_sysguard_cached_swapstat ; 
 int ngx_http_sysguard_do_redirect (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_sysguard_module ; 
 int /*<<< orphan*/  ngx_http_sysguard_update_cpuusage (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_sysguard_update_load (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_sysguard_update_mem (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_sysguard_update_rt (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,double,double) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,double,double) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_sysguard_handler(ngx_http_request_t *r)
{
    ngx_http_sysguard_conf_t  *glcf;
    ngx_int_t                  load_log = 0, swap_log = 0,
                               free_log = 0, rt_log = 0,
                               cpu_log = 0;
    ngx_str_t                 *action = NULL;

    if (r->main->sysguard_set) {
        return NGX_DECLINED;
    }

    glcf = ngx_http_get_module_loc_conf(r, ngx_http_sysguard_module);

    if (!glcf->enable) {
        return NGX_DECLINED;
    }

    r->main->sysguard_set = 1;

    /* load */

    if (glcf->load != NGX_CONF_UNSET) {

        if (ngx_http_sysguard_cached_load_exptime < ngx_time()) {
            ngx_http_sysguard_update_load(r, glcf->interval);
        }

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http sysguard handler load: %1.3f %1.3f %V %V",
                       ngx_http_sysguard_cached_load * 1.0 / 1000,
                       glcf->load * 1.0 / 1000,
                       &r->uri,
                       &glcf->load_action);

        if (ngx_http_sysguard_cached_load > glcf->load) {

            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_OR) {

                ngx_log_error(glcf->log_level, r->connection->log, 0,
                              "sysguard load limited, current:%1.3f conf:%1.3f",
                              ngx_http_sysguard_cached_load * 1.0 / 1000,
                              glcf->load * 1.0 / 1000);

                return ngx_http_sysguard_do_redirect(r, &glcf->load_action);
            } else {
                action = &glcf->load_action;
                load_log = 1;
            }
        } else {
            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND) {
                goto out;
            }
        }
    }

    /* cpu */

    if (glcf->cpuusage != NGX_CONF_UNSET) {

        if (ngx_http_sysguard_cached_cpuusage_exptime < ngx_time()) {
            ngx_http_sysguard_update_cpuusage(r, glcf->interval);
        }

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http sysguard handler cpuusage: %d %d %V %V",
                       ngx_http_sysguard_cached_cpuusage ,
                       glcf->cpuusage,
                       &r->uri,
                       &glcf->cpuusage_action);

        if (ngx_http_sysguard_cached_cpuusage > glcf->cpuusage) {

            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_OR) {

                ngx_log_error(glcf->log_level, r->connection->log, 0,
                              "sysguard cpuusage limited, current:%d conf:%d",
                              ngx_http_sysguard_cached_cpuusage,
                              glcf->cpuusage);

                return ngx_http_sysguard_do_redirect(r, &glcf->cpuusage_action);

            } else {
                action = &glcf->cpuusage_action;
                cpu_log = 1;
            }

        } else {
            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND) {
                goto out;
            }
        }
    }

    /* swap */

    if (glcf->swap != NGX_CONF_UNSET) {

        if (ngx_http_sysguard_cached_mem_exptime < ngx_time()) {
            ngx_http_sysguard_update_mem(r, glcf->interval);
        }

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http sysguard handler swap: %i %i %V %V",
                       ngx_http_sysguard_cached_swapstat,
                       glcf->swap,
                       &r->uri,
                       &glcf->swap_action);

        if (ngx_http_sysguard_cached_swapstat > glcf->swap) {

            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_OR) {

                ngx_log_error(glcf->log_level, r->connection->log, 0,
                              "sysguard swap limited, current:%i conf:%i",
                              ngx_http_sysguard_cached_swapstat,
                              glcf->swap);

                return ngx_http_sysguard_do_redirect(r, &glcf->swap_action);
            } else {
                action = &glcf->swap_action;
                swap_log = 1;
            }
        } else {
            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND) {
                goto out;
            }
        }
    }

    /* mem free */

    if (glcf->free != NGX_CONF_UNSET_SIZE) {

        if (ngx_http_sysguard_cached_mem_exptime < ngx_time()) {
            ngx_http_sysguard_update_mem(r, glcf->interval);
        }

        if (ngx_http_sysguard_cached_free != NGX_CONF_UNSET_SIZE) {

            ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http sysguard handler free: %uz %uz %V %V",
                           ngx_http_sysguard_cached_free,
                           glcf->free,
                           &r->uri,
                           &glcf->free_action);

            if (ngx_http_sysguard_cached_free < glcf->free) {

                if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_OR) {

                    ngx_log_error(glcf->log_level, r->connection->log, 0,
                                  "sysguard free limited, "
                                  "current:%uzM conf:%uzM",
                                  ngx_http_sysguard_cached_free / 1024 / 1024,
                                  glcf->free / 1024 / 1024);

                    return ngx_http_sysguard_do_redirect(r, &glcf->free_action);
                } else {
                    action = &glcf->free_action;
                    free_log = 1;
                }
            } else {
                if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND) {
                    goto out;
                }
            }
        }
    }

    /* response time */

    if (glcf->rt != NGX_CONF_UNSET) {

        if (glcf->rt_ring->cached_rt_exptime < ngx_time()) {
            ngx_http_sysguard_update_rt(r, glcf->interval);
        }

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http sysguard handler rt: %1.3f %1.3f",
                       glcf->rt_ring->cached_rt * 1.0 / 1000,
                       glcf->rt * 1.0 / 1000);

        if (glcf->rt_ring->cached_rt > glcf->rt) {

            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_OR) {

                ngx_log_error(glcf->log_level, r->connection->log, 0,
                              "sysguard rt limited, current:%1.3f conf:%1.3f",
                              glcf->rt_ring->cached_rt * 1.0 / 1000,
                              glcf->rt * 1.0 / 1000);

                return ngx_http_sysguard_do_redirect(r, &glcf->rt_action);
            } else {
                action = &glcf->rt_action;
                rt_log = 1;
            }
        } else {
            if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND) {
                goto out;
            }
        }
    }

    if (glcf->mode == NGX_HTTP_SYSGUARD_MODE_AND && action) {

        if (load_log) {
            ngx_log_error(glcf->log_level, r->connection->log, 0,
                          "sysguard load limited, current:%1.3f conf:%1.3f",
                          ngx_http_sysguard_cached_load * 1.0 / 1000,
                          glcf->load * 1.0 / 1000);
        }

        if (cpu_log) {
            ngx_log_error(glcf->log_level, r->connection->log, 0,
                          "sysguard cpu limited, current:%d conf:%1d",
                          ngx_http_sysguard_cached_cpuusage,
                          glcf->cpuusage);
        }

        if (swap_log) {
            ngx_log_error(glcf->log_level, r->connection->log, 0,
                          "sysguard swap limited, current:%i conf:%i",
                          ngx_http_sysguard_cached_swapstat,
                          glcf->swap);
        }

        if (free_log) {
            ngx_log_error(glcf->log_level, r->connection->log, 0,
                          "sysguard free limited, current:%uzM conf:%uzM",
                          ngx_http_sysguard_cached_free / 1024 / 1024,
                          glcf->free / 1024 / 1024);
        }

        if (rt_log) {
            ngx_log_error(glcf->log_level, r->connection->log, 0,
                          "sysguard rt limited, current:%1.3f conf:%1.3f",
                          glcf->rt_ring->cached_rt * 1.0 / 1000,
                          glcf->rt * 1.0 / 1000);
        }

        return ngx_http_sysguard_do_redirect(r, action);
    }

out:
    return NGX_DECLINED;
}