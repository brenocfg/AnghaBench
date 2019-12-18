#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_7__ {TYPE_1__* args; } ;
typedef  TYPE_2__ ngx_conf_t ;
struct TYPE_8__ {int offset; } ;
typedef  TYPE_3__ ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_6__ {size_t nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * ngx_array_push (int /*<<< orphan*/ *) ; 

char *
ngx_mail_capabilities(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    ngx_str_t    *c, *value;
    ngx_uint_t    i;
    ngx_array_t  *a;

    a = (ngx_array_t *) (p + cmd->offset);

    value = cf->args->elts;

    for (i = 1; i < cf->args->nelts; i++) {
        c = ngx_array_push(a);
        if (c == NULL) {
            return NGX_CONF_ERROR;
        }

        *c = value[i];
    }

    return NGX_CONF_OK;
}