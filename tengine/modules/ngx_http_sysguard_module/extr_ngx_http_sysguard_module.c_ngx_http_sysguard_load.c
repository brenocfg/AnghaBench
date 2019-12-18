#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {char* data; int len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_10__ {char* data; int len; } ;
struct TYPE_12__ {size_t load; TYPE_2__ load_action; } ;
typedef  TYPE_4__ ngx_http_sysguard_conf_t ;
struct TYPE_13__ {TYPE_1__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_9__ {int nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_CONF_UNSET ; 
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 size_t ngx_atofp (char*,int,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 size_t ngx_ncpu ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
ngx_http_sysguard_load(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_sysguard_conf_t  *glcf = conf;

    ngx_str_t  *value;
    ngx_uint_t  i, scale;

    value = cf->args->elts;
    i = 1;
    scale = 1;

    if (ngx_strncmp(value[i].data, "load=", 5) == 0) {

        if (glcf->load != NGX_CONF_UNSET) {
            return "is duplicate";
        }

        if (value[i].len == 5) {
            goto invalid;
        }

        value[i].data += 5;
        value[i].len -= 5;

        if (ngx_strncmp(value[i].data, "ncpu*", 5) == 0) {
            value[i].data += 5;
            value[i].len -= 5;
            scale = ngx_ncpu;
        }

        glcf->load = ngx_atofp(value[i].data, value[i].len, 3);
        if (glcf->load == NGX_ERROR) {
            goto invalid;
        }

        glcf->load = glcf->load * scale;

        if (cf->args->nelts == 2) {
            return NGX_CONF_OK;
        }

        i++;

        if (ngx_strncmp(value[i].data, "action=", 7) != 0) {
            goto invalid;
        }

        if (value[i].len == 7) {
            goto invalid;
        }

        if (value[i].data[7] != '/' && value[i].data[7] != '@') {
            goto invalid;
        }

        glcf->load_action.data = value[i].data + 7;
        glcf->load_action.len = value[i].len - 7;

        return NGX_CONF_OK;
    }

invalid:

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid parameter \"%V\"", &value[i]);

    return NGX_CONF_ERROR;
}