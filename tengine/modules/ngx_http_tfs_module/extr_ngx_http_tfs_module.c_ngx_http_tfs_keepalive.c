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
struct TYPE_10__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/ * conn_pool; } ;
typedef  TYPE_3__ ngx_http_tfs_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_connection_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ ngx_command_t ;
struct TYPE_9__ {size_t nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atoi (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ngx_http_connection_pool_init (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_tfs_keepalive(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_tfs_main_conf_t  *tmcf = conf;

    ngx_int_t                    max_cached, bucket_count;
    ngx_str_t                   *value, s;
    ngx_uint_t                   i;
    ngx_http_connection_pool_t  *p;

    value = cf->args->elts;
    max_cached = 0;
    bucket_count = 0;

    for (i = 1; i < cf->args->nelts; i++) {
        if (ngx_strncmp(value[i].data, "max_cached=", 11) == 0) {

            s.len = value[i].len - 11;
            s.data = value[i].data + 11;

            max_cached = ngx_atoi(s.data, s.len);

            if (max_cached == NGX_ERROR || max_cached == 0) {
                goto invalid;
            }
            continue;
        }

        if (ngx_strncmp(value[i].data, "bucket_count=", 13) == 0) {

            s.len = value[i].len - 13;
            s.data = value[i].data + 13;

            bucket_count = ngx_atoi(s.data, s.len);
            if (bucket_count == NGX_ERROR || bucket_count == 0) {
                goto invalid;
            }
            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[i]);
        return NGX_CONF_ERROR;
    }

    p = ngx_http_connection_pool_init(cf->pool, max_cached, bucket_count);
    if (p == NULL) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "connection pool init failed");
        return NGX_CONF_ERROR;
    }

    tmcf->conn_pool = p;
    return NGX_CONF_OK;

invalid:
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid value \"%V\" in \"%V\" directive",
                       &value[i], &cmd->name);
    return NGX_CONF_ERROR;
}