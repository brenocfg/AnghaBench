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
typedef  void ngx_http_browser_conf_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_conf_t ;

/* Variables and functions */
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
ngx_http_browser_create_conf(ngx_conf_t *cf)
{
    ngx_http_browser_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_browser_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc():
     *
     *     conf->modern_browsers = NULL;
     *     conf->ancient_browsers = NULL;
     *     conf->modern_browser_value = NULL;
     *     conf->ancient_browser_value = NULL;
     *
     *     conf->modern_unlisted_browsers = 0;
     *     conf->netscape4 = 0;
     */

    return conf;
}