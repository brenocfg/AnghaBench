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
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {char* data; scalar_t__ len; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_17__ {TYPE_2__* user_defined_str; int /*<<< orphan*/ * user_select; } ;
typedef  TYPE_5__ ngx_http_reqstat_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_15__ {scalar_t__ len; char* data; } ;
struct TYPE_14__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_13__ {int nelts; TYPE_4__* elts; } ;
struct TYPE_12__ {scalar_t__ index; TYPE_3__ name; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_HTTP_REQSTAT_RSRV ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 TYPE_11__* REQSTAT_RSRV_VARIABLES ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 int* ngx_array_push_n (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* ngx_http_conf_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 scalar_t__ ngx_strncmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static char *
ngx_http_reqstat_show_field(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_int_t                  valid, *index;
    ngx_str_t                 *value, *user;
    ngx_uint_t                 i, j;
    ngx_http_reqstat_conf_t   *rmcf, *rlcf;

    rlcf = conf;
    rmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_reqstat_module);

    rlcf->user_select = ngx_array_create(cf->pool, cf->args->nelts - 1,
                                         sizeof(ngx_int_t));
    if (rlcf->user_select == NULL) {
        return NGX_CONF_ERROR;
    }

    index = ngx_array_push_n(rlcf->user_select, cf->args->nelts - 1);
    if (index == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;
    for (i = 1; i < cf->args->nelts; i++) {
        valid = 0;

        if (value[i].data[0] == '$') {
            value[i].data++;
            value[i].len--;

            if (rmcf->user_defined_str) {

                user = rmcf->user_defined_str->elts;

                for (j = 0; j < rmcf->user_defined_str->nelts; j++) {
                    if (value[i].len != user[j].len
                            || ngx_strncmp(value[i].data, user[j].data, value[i].len)
                            != 0)
                    {
                        continue;
                    }

                    *index++ = NGX_HTTP_REQSTAT_RSRV + j;
                    valid = 1;
                    break;
                }
            }

        } else {
            for (j = 0; j < NGX_HTTP_REQSTAT_RSRV; j++) {
                if (value[i].len != REQSTAT_RSRV_VARIABLES[j].name.len
                    || ngx_strncmp(REQSTAT_RSRV_VARIABLES[j].name.data,
                                   value[i].data, value[i].len) != 0)
                {
                    continue;
                }

                *index++ = REQSTAT_RSRV_VARIABLES[j].index;
                valid = 1;
                break;
            }
        }

        if (!valid) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "field \"%V\" does not exist",
                          &value[i]);

            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}