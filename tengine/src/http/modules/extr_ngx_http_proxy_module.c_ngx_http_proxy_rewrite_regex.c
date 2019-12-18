#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_9__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int /*<<< orphan*/  options; TYPE_2__ err; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_3__ ngx_regex_compile_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/ * regex; } ;
struct TYPE_11__ {int /*<<< orphan*/  handler; TYPE_1__ pattern; } ;
typedef  TYPE_4__ ngx_http_proxy_rewrite_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int NGX_MAX_CONF_ERRSTR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_REGEX_CASELESS ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_proxy_rewrite_regex_handler ; 
 int /*<<< orphan*/ * ngx_http_regex_compile (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_rewrite_regex(ngx_conf_t *cf, ngx_http_proxy_rewrite_t *pr,
    ngx_str_t *regex, ngx_uint_t caseless)
{
#if (NGX_PCRE)
    u_char               errstr[NGX_MAX_CONF_ERRSTR];
    ngx_regex_compile_t  rc;

    ngx_memzero(&rc, sizeof(ngx_regex_compile_t));

    rc.pattern = *regex;
    rc.err.len = NGX_MAX_CONF_ERRSTR;
    rc.err.data = errstr;

    if (caseless) {
        rc.options = NGX_REGEX_CASELESS;
    }

    pr->pattern.regex = ngx_http_regex_compile(cf, &rc);
    if (pr->pattern.regex == NULL) {
        return NGX_ERROR;
    }

    pr->handler = ngx_http_proxy_rewrite_regex_handler;

    return NGX_OK;

#else

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "using regex \"%V\" requires PCRE library", regex);
    return NGX_ERROR;

#endif
}