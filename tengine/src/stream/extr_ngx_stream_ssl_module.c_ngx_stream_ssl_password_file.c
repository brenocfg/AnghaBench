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
struct TYPE_7__ {int /*<<< orphan*/ * passwords; } ;
typedef  TYPE_2__ ngx_stream_ssl_conf_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_8__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/ * ngx_ssl_read_password_file (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_stream_ssl_password_file(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_ssl_conf_t  *scf = conf;

    ngx_str_t  *value;

    if (scf->passwords != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    scf->passwords = ngx_ssl_read_password_file(cf, &value[1]);

    if (scf->passwords == NULL) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}