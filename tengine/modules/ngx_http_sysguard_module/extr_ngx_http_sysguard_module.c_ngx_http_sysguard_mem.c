#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {char* data; int len; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_13__ {char* data; int len; } ;
struct TYPE_11__ {char* data; int len; } ;
struct TYPE_15__ {scalar_t__ swap; size_t free; TYPE_3__ free_action; TYPE_1__ swap_action; } ;
typedef  TYPE_5__ ngx_http_sysguard_conf_t ;
struct TYPE_16__ {TYPE_2__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_12__ {int nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 size_t NGX_CONF_UNSET_SIZE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atofp (char*,int,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 size_t ngx_parse_size (TYPE_4__*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
ngx_http_sysguard_mem(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_sysguard_conf_t  *glcf = conf;

    ngx_str_t  *value, ss;
    ngx_uint_t  i;

    value = cf->args->elts;
    i = 1;

    if (ngx_strncmp(value[i].data, "swapratio=", 10) == 0) {

        if (glcf->swap != NGX_CONF_UNSET) {
            return "is duplicate";
        }

        if (value[i].data[value[i].len - 1] != '%') {
            goto invalid;
        }

        glcf->swap = ngx_atofp(value[i].data + 10, value[i].len - 11, 2);
        if (glcf->swap == NGX_ERROR) {
            goto invalid;
        }

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

        glcf->swap_action.data = value[i].data + 7;
        glcf->swap_action.len = value[i].len - 7;

        return NGX_CONF_OK;

    } else if (ngx_strncmp(value[i].data, "free=", 5) == 0) {

        if (glcf->free != NGX_CONF_UNSET_SIZE) {
            return "is duplicate";
        }

        ss.data = value[i].data + 5;
        ss.len = value[i].len - 5;

        glcf->free = ngx_parse_size(&ss);
        if (glcf->free == (size_t) NGX_ERROR) {
            goto invalid;
        }

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

        glcf->free_action.data = value[i].data + 7;
        glcf->free_action.len = value[i].len - 7;

        return NGX_CONF_OK;
    }

invalid:

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid parameter \"%V\"", &value[i]);

    return NGX_CONF_ERROR;
}