#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * perl; } ;
typedef  TYPE_1__ ngx_http_perl_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 scalar_t__ NGX_CONF_OK ; 
 scalar_t__ ngx_http_perl_init_interpreter (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static char *
ngx_http_perl_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_perl_main_conf_t *pmcf = conf;

    if (pmcf->perl == NULL) {
        if (ngx_http_perl_init_interpreter(cf, pmcf) != NGX_CONF_OK) {
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}