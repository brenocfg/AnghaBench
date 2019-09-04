#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_referer_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_add_regex_referer(ngx_conf_t *cf, ngx_http_referer_conf_t *rlcf,
    ngx_str_t *name)
{
#if (NGX_PCRE)
    ngx_regex_elt_t      *re;
    ngx_regex_compile_t   rc;
    u_char                errstr[NGX_MAX_CONF_ERRSTR];

    if (name->len == 1) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "empty regex in \"%V\"", name);
        return NGX_ERROR;
    }

    if (rlcf->regex == NGX_CONF_UNSET_PTR) {
        rlcf->regex = ngx_array_create(cf->pool, 2, sizeof(ngx_regex_elt_t));
        if (rlcf->regex == NULL) {
            return NGX_ERROR;
        }
    }

    re = ngx_array_push(rlcf->regex);
    if (re == NULL) {
        return NGX_ERROR;
    }

    name->len--;
    name->data++;

    ngx_memzero(&rc, sizeof(ngx_regex_compile_t));

    rc.pattern = *name;
    rc.pool = cf->pool;
    rc.options = NGX_REGEX_CASELESS;
    rc.err.len = NGX_MAX_CONF_ERRSTR;
    rc.err.data = errstr;

    if (ngx_regex_compile(&rc) != NGX_OK) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "%V", &rc.err);
        return NGX_ERROR;
    }

    re->regex = rc.regex;
    re->name = name->data;

    return NGX_OK;

#else

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "the using of the regex \"%V\" requires PCRE library",
                       name);

    return NGX_ERROR;

#endif
}