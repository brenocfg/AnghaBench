#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_12__ {scalar_t__ rcs_interval; TYPE_2__ lock_file; } ;
typedef  TYPE_3__ ngx_http_tfs_upstream_t ;
struct TYPE_13__ {int /*<<< orphan*/  cycle; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_10__ {size_t nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_MIN_TIMER_DELAY ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_parse_time (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_tfs_rcs_heartbeat(ngx_conf_t *cf, ngx_http_tfs_upstream_t *tu)
{
    ngx_str_t  *value, s;
    ngx_msec_t  interval;
    ngx_uint_t  i;

    value = cf->args->elts;

    for (i = 1; i < cf->args->nelts; i++) {
        if (ngx_strncmp(value[i].data, "lock_file=", 10) == 0) {
            s.data = value[i].data + 10;
            s.len = value[i].len - 10;

            if (ngx_conf_full_name(cf->cycle, &s, 0) != NGX_OK) {
                goto rcs_timers_error;
            }

            tu->lock_file = s;
            continue;
        }

        if (ngx_strncmp(value[i].data, "interval=", 9) == 0) {
            s.data = value[i].data + 9;
            s.len = value[i].len - 9;

            interval = ngx_parse_time(&s, 0);

            if (interval == (ngx_msec_t) NGX_ERROR) {
                return "invalid value";
            }

            tu->rcs_interval = interval;
            continue;
        }

        goto rcs_timers_error;
    }

    if (tu->lock_file.len == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "tfs_poll directive must have lock file");
        return NGX_CONF_ERROR;
    }

    if (tu->rcs_interval < NGX_HTTP_TFS_MIN_TIMER_DELAY) {
        tu->rcs_interval = NGX_HTTP_TFS_MIN_TIMER_DELAY;
        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                           "tfs_poll interval is small, "
                           "so reset this value to 1000");
    }

    return NGX_CONF_OK;

rcs_timers_error:
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid value \"%V\" in \"%V\" directive",
                       &value[i], &value[0]);
    return NGX_CONF_ERROR;
}