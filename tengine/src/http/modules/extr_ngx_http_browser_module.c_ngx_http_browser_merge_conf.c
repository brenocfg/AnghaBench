#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_7__ {scalar_t__ skip; unsigned int version; int /*<<< orphan*/  name; int /*<<< orphan*/  add; } ;
typedef  TYPE_1__ ngx_http_modern_browser_t ;
struct TYPE_8__ {scalar_t__ modern_unlisted_browsers; scalar_t__ netscape4; int /*<<< orphan*/ * ancient_browser_value; int /*<<< orphan*/ * modern_browser_value; int /*<<< orphan*/ * ancient_browsers; TYPE_6__* modern_browsers; } ;
typedef  TYPE_2__ ngx_http_browser_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_10__ {size_t nelts; TYPE_1__* elts; } ;
struct TYPE_9__ {size_t skip; int /*<<< orphan*/  name; int /*<<< orphan*/  add; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_1__* ngx_array_push (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_cpystrn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ngx_http_modern_browser_masks ; 
 int /*<<< orphan*/  ngx_http_modern_browser_sort ; 
 int /*<<< orphan*/  ngx_http_variable_true_value ; 
 int /*<<< orphan*/  ngx_qsort (TYPE_1__*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_browser_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_browser_conf_t *prev = parent;
    ngx_http_browser_conf_t *conf = child;

    ngx_uint_t                  i, n;
    ngx_http_modern_browser_t  *browsers, *opera;

    /*
     * At the merge the skip field is used to store the browser slot,
     * it will be used in sorting and then will overwritten
     * with a real skip value.  The zero value means Opera.
     */

    if (conf->modern_browsers == NULL && conf->modern_unlisted_browsers == 0) {
        conf->modern_browsers = prev->modern_browsers;
        conf->modern_unlisted_browsers = prev->modern_unlisted_browsers;

    } else if (conf->modern_browsers != NULL) {
        browsers = conf->modern_browsers->elts;

        for (i = 0; i < conf->modern_browsers->nelts; i++) {
            if (browsers[i].skip == 0) {
                goto found;
            }
        }

        /*
         * Opera may contain MSIE string, so if Opera was not enumerated
         * as modern browsers, then add it and set a unreachable version
         */

        opera = ngx_array_push(conf->modern_browsers);
        if (opera == NULL) {
            return NGX_CONF_ERROR;
        }

        opera->skip = 0;
        opera->version = 4001000000U;

        browsers = conf->modern_browsers->elts;

found:

        ngx_qsort(browsers, (size_t) conf->modern_browsers->nelts,
                  sizeof(ngx_http_modern_browser_t),
                  ngx_http_modern_browser_sort);

        for (i = 0; i < conf->modern_browsers->nelts; i++) {
             n = browsers[i].skip;

             browsers[i].skip = ngx_http_modern_browser_masks[n].skip;
             browsers[i].add = ngx_http_modern_browser_masks[n].add;
             (void) ngx_cpystrn(browsers[i].name,
                                ngx_http_modern_browser_masks[n].name, 12);
        }
    }

    if (conf->ancient_browsers == NULL && conf->netscape4 == 0) {
        conf->ancient_browsers = prev->ancient_browsers;
        conf->netscape4 = prev->netscape4;
    }

    if (conf->modern_browser_value == NULL) {
        conf->modern_browser_value = prev->modern_browser_value;
    }

    if (conf->modern_browser_value == NULL) {
        conf->modern_browser_value = &ngx_http_variable_true_value;
    }

    if (conf->ancient_browser_value == NULL) {
        conf->ancient_browser_value = prev->ancient_browser_value;
    }

    if (conf->ancient_browser_value == NULL) {
        conf->ancient_browser_value = &ngx_http_variable_true_value;
    }

    return NGX_CONF_OK;
}