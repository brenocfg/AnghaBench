#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  uri; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_fastcgi_loc_conf_t ;
struct TYPE_11__ {int /*<<< orphan*/  script_name; } ;
typedef  TYPE_2__ ngx_http_fastcgi_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_http_fastcgi_ctx_t *
ngx_http_fastcgi_split(ngx_http_request_t *r, ngx_http_fastcgi_loc_conf_t *flcf)
{
    ngx_http_fastcgi_ctx_t       *f;
#if (NGX_PCRE)
    ngx_int_t                     n;
    int                           captures[(1 + 2) * 3];

    f = ngx_http_get_module_ctx(r, ngx_http_fastcgi_module);

    if (f == NULL) {
        f = ngx_pcalloc(r->pool, sizeof(ngx_http_fastcgi_ctx_t));
        if (f == NULL) {
            return NULL;
        }

        ngx_http_set_ctx(r, f, ngx_http_fastcgi_module);
    }

    if (f->script_name.len) {
        return f;
    }

    if (flcf->split_regex == NULL) {
        f->script_name = r->uri;
        return f;
    }

    n = ngx_regex_exec(flcf->split_regex, &r->uri, captures, (1 + 2) * 3);

    if (n >= 0) { /* match */
        f->script_name.len = captures[3] - captures[2];
        f->script_name.data = r->uri.data + captures[2];

        f->path_info.len = captures[5] - captures[4];
        f->path_info.data = r->uri.data + captures[4];

        return f;
    }

    if (n == NGX_REGEX_NO_MATCHED) {
        f->script_name = r->uri;
        return f;
    }

    ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                  ngx_regex_exec_n " failed: %i on \"%V\" using \"%V\"",
                  n, &r->uri, &flcf->split_name);
    return NULL;

#else

    f = ngx_http_get_module_ctx(r, ngx_http_fastcgi_module);

    if (f == NULL) {
        f = ngx_pcalloc(r->pool, sizeof(ngx_http_fastcgi_ctx_t));
        if (f == NULL) {
            return NULL;
        }

        ngx_http_set_ctx(r, f, ngx_http_fastcgi_module);
    }

    f->script_name = r->uri;

    return f;

#endif
}