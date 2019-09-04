#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ secret; int /*<<< orphan*/ * md5; int /*<<< orphan*/ * variable; } ;
typedef  TYPE_2__ ngx_http_secure_link_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_secure_link_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_secure_link_conf_t *prev = parent;
    ngx_http_secure_link_conf_t *conf = child;

    if (conf->secret.data) {
        if (conf->variable || conf->md5) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "\"secure_link_secret\" cannot be mixed with "
                               "\"secure_link\" and \"secure_link_md5\"");
            return NGX_CONF_ERROR;
        }

        return NGX_CONF_OK;
    }

    if (conf->variable == NULL) {
        conf->variable = prev->variable;
    }

    if (conf->md5 == NULL) {
        conf->md5 = prev->md5;
    }

    if (conf->variable == NULL && conf->md5 == NULL) {
        conf->secret = prev->secret;
    }

    return NGX_CONF_OK;
}