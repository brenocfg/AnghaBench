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
typedef  int time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {char* data; int len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_11__ {char* data; int len; } ;
struct TYPE_13__ {int cpu_interval; scalar_t__ cpuusage; TYPE_2__ cpuusage_action; } ;
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
 int ngx_parse_time (TYPE_3__*,int) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
ngx_http_sysguard_cpuusage(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_sysguard_conf_t  *glcf = conf;

    ngx_str_t  *value;
    ngx_uint_t  i;

    value = cf->args->elts;
    glcf->cpu_interval = 3;

    for (i = 1; i < cf->args->nelts; i++) {
        if (ngx_strncmp(value[i].data, "usage=", 6) == 0) {

            if (glcf->cpuusage != NGX_CONF_UNSET) {
                return "is duplicate";
            }

            if (value[i].len == 6) {
                goto invalid;
            }

            value[i].data += 6;
            value[i].len -= 6;

            glcf->cpuusage = ngx_atofp(value[i].data, value[i].len, 2);
            if (glcf->cpuusage == NGX_ERROR) {
                goto invalid;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "period=", 7) == 0) {

            if (value[i].len == 7) {
                goto invalid;
            }

            value[i].data += 7;
            value[i].len -= 7;
            glcf->cpu_interval = ngx_parse_time(&value[i], 1);
            if (glcf->cpu_interval == (time_t) NGX_ERROR) {
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

            glcf->cpuusage_action.data = value[i].data + 7;
            glcf->cpuusage_action.len = value[i].len - 7;

            continue;
        }

    }

    return NGX_CONF_OK;

invalid:

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid parameter \"%V\"", &value[i]);

    return NGX_CONF_ERROR;
}