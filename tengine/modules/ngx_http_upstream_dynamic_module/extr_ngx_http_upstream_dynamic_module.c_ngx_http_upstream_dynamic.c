#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {scalar_t__ init_upstream; } ;
struct TYPE_16__ {TYPE_1__ peer; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  fallback; scalar_t__ fail_timeout; scalar_t__ original_init_upstream; } ;
typedef  TYPE_5__ ngx_http_upstream_dynamic_srv_conf_t ;
struct TYPE_18__ {TYPE_2__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_14__ {size_t nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_DYN_RESOLVE_NEXT ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_DYN_RESOLVE_SHUTDOWN ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_DYN_RESOLVE_STALE ; 
 TYPE_4__* ngx_http_conf_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_conf_upstream_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_module ; 
 scalar_t__ ngx_http_upstream_init_dynamic ; 
 scalar_t__ ngx_http_upstream_init_round_robin ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 scalar_t__ ngx_parse_time (TYPE_3__*,int) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static char *
ngx_http_upstream_dynamic(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_upstream_srv_conf_t            *uscf;
    ngx_http_upstream_dynamic_srv_conf_t    *dcf;
    ngx_str_t   *value, s;
    ngx_uint_t   i;
    time_t       fail_timeout;
    ngx_int_t    fallback;

    uscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_upstream_module);

    dcf = ngx_http_conf_upstream_srv_conf(uscf,
                                          ngx_http_upstream_dynamic_module);

    if (dcf->original_init_upstream) {
        return "is duplicate";
    }

    dcf->original_init_upstream = uscf->peer.init_upstream
                                  ? uscf->peer.init_upstream
                                  : ngx_http_upstream_init_round_robin;

    uscf->peer.init_upstream = ngx_http_upstream_init_dynamic;

    /* read options */

    value = cf->args->elts;

    for (i = 1; i < cf->args->nelts; i++) {

        if (ngx_strncmp(value[i].data, "fail_timeout=", 13) == 0) {

            s.len = value[i].len - 13;
            s.data = &value[i].data[13];

            fail_timeout = ngx_parse_time(&s, 1);

            if (fail_timeout == (time_t) NGX_ERROR) {
                return "invalid fail_timeout";
            }

            dcf->fail_timeout = fail_timeout;

            continue;
        }

        if (ngx_strncmp(value[i].data, "fallback=", 9) == 0) {

            s.len = value[i].len - 9;
            s.data = &value[i].data[9];

            if (ngx_strncmp(s.data, "next", 4) == 0) {
                fallback = NGX_HTTP_UPSTREAM_DYN_RESOLVE_NEXT;
            } else if (ngx_strncmp(s.data, "stale", 5) == 0) {
                fallback = NGX_HTTP_UPSTREAM_DYN_RESOLVE_STALE;
            } else if (ngx_strncmp(s.data, "shutdown", 8) == 0) {
                fallback = NGX_HTTP_UPSTREAM_DYN_RESOLVE_SHUTDOWN;
            } else {
                return "invalid fallback action";
            }

            dcf->fallback = fallback;

            continue;
        }
    }

    return NGX_CONF_OK;
}