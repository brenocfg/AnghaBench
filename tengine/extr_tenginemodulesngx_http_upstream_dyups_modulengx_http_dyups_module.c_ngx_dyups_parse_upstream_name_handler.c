#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_7__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_5__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *
ngx_dyups_parse_upstream_name_handler(ngx_conf_t *cf, ngx_command_t *dummy,
    void *conf)
{
    ngx_str_t   *name = conf;
    ngx_str_t   *value;

    if (cf->args->nelts != 2) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    if (value[0].len != 8 || ngx_strncmp(value[0].data, "upstream", 8) != 0) {
        return NGX_CONF_ERROR;
    }

    *name = value[1];

    return NGX_CONF_OK;
}