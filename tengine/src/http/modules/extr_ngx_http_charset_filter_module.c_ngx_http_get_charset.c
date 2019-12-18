#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  size_t ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {TYPE_1__ name; } ;
typedef  TYPE_4__ ngx_http_charset_t ;
struct TYPE_9__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_12__ {TYPE_2__ charsets; } ;
typedef  TYPE_5__ ngx_http_charset_main_conf_t ;

/* Variables and functions */
 size_t NGX_HTTP_NO_CHARSET ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 TYPE_5__* ngx_http_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_get_charset(ngx_http_request_t *r, ngx_str_t *name)
{
    ngx_uint_t                     i, n;
    ngx_http_charset_t            *charset;
    ngx_http_charset_main_conf_t  *mcf;

    mcf = ngx_http_get_module_main_conf(r, ngx_http_charset_filter_module);

    charset = mcf->charsets.elts;
    n = mcf->charsets.nelts;

    for (i = 0; i < n; i++) {
        if (charset[i].name.len != name->len) {
            continue;
        }

        if (ngx_strncasecmp(charset[i].name.data, name->data, name->len) == 0) {
            return i;
        }
    }

    return NGX_HTTP_NO_CHARSET;
}