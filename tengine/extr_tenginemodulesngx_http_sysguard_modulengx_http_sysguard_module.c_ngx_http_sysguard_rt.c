#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {char* data; int len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_11__ {char* data; int len; } ;
struct TYPE_13__ {scalar_t__ rt; scalar_t__ rt_period; TYPE_2__ rt_action; } ;
typedef  TYPE_4__ ngx_http_sysguard_conf_t ;
struct TYPE_14__ {TYPE_1__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_10__ {size_t nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atofp (char*,int,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 scalar_t__ ngx_parse_time (TYPE_3__*,int) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
ngx_http_sysguard_rt(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_sysguard_conf_t  *glcf = conf;

    ngx_str_t  *value, ss;
    ngx_uint_t  i;

    value = cf->args->elts;

    for (i = 1; i < cf->args->nelts; i++) {
        if (ngx_strncmp(value[i].data, "rt=", 3) == 0) {

            if (glcf->rt != NGX_CONF_UNSET) {
                return "is duplicate";
            }

            glcf->rt = ngx_atofp(value[i].data + 3, value[i].len - 3, 3);
            if (glcf->rt == NGX_ERROR) {
                goto invalid;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "period=", 7) == 0) {

            ss.data = value[i].data + 7;
            ss.len = value[i].len - 7;

            glcf->rt_period = ngx_parse_time(&ss, 1);
            if (glcf->rt_period == NGX_ERROR) {
                goto invalid;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "action=", 7) == 0) {

            if (value[i].len == 7) {
                goto invalid;
            }

            if (value[i].data[7] != '/' && value[i].data[7] != '@') {
                goto invalid;
            }

            glcf->rt_action.data = value[i].data + 7;
            glcf->rt_action.len = value[i].len - 7;

            continue;
        }
    }

    return NGX_CONF_OK;

invalid:

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid parameter \"%V\"", &value[i]);

    return NGX_CONF_ERROR;
}