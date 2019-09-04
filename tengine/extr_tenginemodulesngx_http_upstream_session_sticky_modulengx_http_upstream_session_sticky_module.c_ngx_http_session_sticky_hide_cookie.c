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
struct TYPE_14__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_15__ {int uri_part; int no_resolve; TYPE_2__ url; } ;
typedef  TYPE_3__ ngx_url_t ;
struct TYPE_16__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_17__ {int /*<<< orphan*/ * uscf; } ;
typedef  TYPE_5__ ngx_http_ss_loc_conf_t ;
struct TYPE_18__ {TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_13__ {scalar_t__ elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_deprecated (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_deprecated_session_sticky_header ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_session_sticky_hide_cookie(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_http_ss_loc_conf_t  *slcf = conf;

    size_t      add;
    ngx_str_t  *value;
    ngx_url_t   u;

    value = (ngx_str_t *) cf->args->elts;
    if (ngx_strncmp(value[0].data, "session_sticky_header", 21) == 0) {
        ngx_conf_deprecated(cf,
                            &ngx_conf_deprecated_session_sticky_header, NULL);
    }

    if (ngx_strncmp(value[1].data, "upstream=", 9) == 0) {
        add = 9;
        ngx_memzero(&u, sizeof(ngx_url_t));

        u.url.len = value[1].len - add;
        u.url.data = value[1].data + add;
        u.uri_part = 1;
        u.no_resolve = 1;

        slcf->uscf = ngx_http_upstream_add(cf, &u, 0);
        if (slcf->uscf == NULL) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid upstream name");
            return NGX_CONF_ERROR;
        }
        return NGX_CONF_OK;
    }

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid argument of \"%V\"",
                       &value[1]);
    return NGX_CONF_ERROR;
}