#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_pending_timers; int max_running_timers; int /*<<< orphan*/  cycle; } ;
typedef  TYPE_1__ ngx_http_lua_main_conf_t ;
struct TYPE_5__ {int /*<<< orphan*/  cycle; } ;
typedef  TYPE_2__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int NGX_CONF_UNSET ; 

__attribute__((used)) static char *
ngx_http_lua_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_lua_main_conf_t *lmcf = conf;

#if (NGX_PCRE)
    if (lmcf->regex_cache_max_entries == NGX_CONF_UNSET) {
        lmcf->regex_cache_max_entries = 1024;
    }

    if (lmcf->regex_match_limit == NGX_CONF_UNSET) {
        lmcf->regex_match_limit = 0;
    }
#endif

    if (lmcf->max_pending_timers == NGX_CONF_UNSET) {
        lmcf->max_pending_timers = 1024;
    }

    if (lmcf->max_running_timers == NGX_CONF_UNSET) {
        lmcf->max_running_timers = 256;
    }

#if (NGX_HTTP_LUA_HAVE_SA_RESTART)
    if (lmcf->set_sa_restart == NGX_CONF_UNSET) {
        lmcf->set_sa_restart = 1;
    }
#endif

#if (NGX_HTTP_LUA_HAVE_MALLOC_TRIM)
    if (lmcf->malloc_trim_cycle == NGX_CONF_UNSET_UINT) {
        lmcf->malloc_trim_cycle = 1000;  /* number of reqs */
    }
#endif

    lmcf->cycle = cf->cycle;

    return NGX_CONF_OK;
}