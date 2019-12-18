#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {int requires_log; scalar_t__ malloc_trim_cycle; } ;
typedef  TYPE_3__ ngx_http_lua_main_conf_t ;
struct TYPE_10__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_lua_malloc_trim(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
#if (NGX_HTTP_LUA_HAVE_MALLOC_TRIM)

    ngx_int_t       nreqs;
    ngx_str_t      *value;

    ngx_http_lua_main_conf_t    *lmcf = conf;

    value = cf->args->elts;

    nreqs = ngx_atoi(value[1].data, value[1].len);
    if (nreqs == NGX_ERROR) {
        return "invalid number in the 1st argument";
    }

    lmcf->malloc_trim_cycle = (ngx_uint_t) nreqs;

    if (nreqs == 0) {
        return NGX_CONF_OK;
    }

    lmcf->requires_log = 1;

#else

    ngx_conf_log_error(NGX_LOG_WARN, cf, 0, "lua_malloc_trim is not supported "
                       "on this platform, ignored");

#endif
    return NGX_CONF_OK;
}