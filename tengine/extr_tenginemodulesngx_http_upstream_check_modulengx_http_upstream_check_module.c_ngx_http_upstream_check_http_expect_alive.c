#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_15__ {size_t status_alive; } ;
struct TYPE_17__ {TYPE_3__ code; } ;
typedef  TYPE_5__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_18__ {TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_14__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {size_t mask; TYPE_2__ name; } ;
typedef  TYPE_7__ ngx_conf_bitmask_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_13__ {size_t nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 TYPE_7__* ngx_check_http_expect_alive_masks ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_conf_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 
 scalar_t__ ngx_strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_upstream_check_http_expect_alive(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_str_t                           *value;
    ngx_uint_t                           bit, i, m;
    ngx_conf_bitmask_t                  *mask;
    ngx_http_upstream_check_srv_conf_t  *ucscf;

    value = cf->args->elts;
    mask = ngx_check_http_expect_alive_masks;

    ucscf = ngx_http_conf_get_module_srv_conf(cf,
                                              ngx_http_upstream_check_module);
    bit = 0;

    for (i = 1; i < cf->args->nelts; i++) {
        for (m = 0; mask[m].name.len != 0; m++) {

            if (mask[m].name.len != value[i].len
                || ngx_strcasecmp(mask[m].name.data, value[i].data) != 0)
            {
                continue;
            }

            if (bit & mask[m].mask) {
                ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                                   "duplicate value \"%s\"", value[i].data);

            } else {
                bit |= mask[m].mask;
            }

            break;
        }

        if (mask[m].name.len == 0) {
            ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                               "invalid value \"%s\"", value[i].data);

            return NGX_CONF_ERROR;
        }
    }

    ucscf->code.status_alive = bit;

    return NGX_CONF_OK;
}