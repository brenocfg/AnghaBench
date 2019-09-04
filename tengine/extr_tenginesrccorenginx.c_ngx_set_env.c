#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {size_t len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_3__ ngx_core_conf_t ;
struct TYPE_10__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_set_env(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_core_conf_t  *ccf = conf;

    ngx_str_t   *value, *var;
    ngx_uint_t   i;

    var = ngx_array_push(&ccf->env);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;
    *var = value[1];

    for (i = 0; i < value[1].len; i++) {

        if (value[1].data[i] == '=') {

            var->len = i;

            return NGX_CONF_OK;
        }
    }

    return NGX_CONF_OK;
}