#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {TYPE_2__ uri; } ;
typedef  TYPE_3__ ngx_http_auth_request_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *
ngx_http_auth_request(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_auth_request_conf_t *arcf = conf;

    ngx_str_t        *value;

    if (arcf->uri.data != NULL) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "off") == 0) {
        arcf->uri.len = 0;
        arcf->uri.data = (u_char *) "";

        return NGX_CONF_OK;
    }

    arcf->uri = value[1];

    return NGX_CONF_OK;
}