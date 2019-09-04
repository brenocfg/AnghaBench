#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * rules; } ;
typedef  TYPE_1__ ngx_http_access_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 

__attribute__((used)) static char *
ngx_http_access_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_access_loc_conf_t  *prev = parent;
    ngx_http_access_loc_conf_t  *conf = child;

    if (conf->rules == NULL
#if (NGX_HAVE_INET6)
        && conf->rules6 == NULL
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
        && conf->rules_un == NULL
#endif
    ) {
        conf->rules = prev->rules;
#if (NGX_HAVE_INET6)
        conf->rules6 = prev->rules6;
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
        conf->rules_un = prev->rules_un;
#endif
    }

    return NGX_CONF_OK;
}