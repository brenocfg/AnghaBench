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
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ngx_http_upstream_check_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_get_check_status_format_conf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_string (char*) ; 

__attribute__((used)) static char *
ngx_http_upstream_check_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child)
{
    ngx_str_t                            format = ngx_string("html");
    ngx_http_upstream_check_loc_conf_t  *prev = parent;
    ngx_http_upstream_check_loc_conf_t  *conf = child;

    ngx_conf_merge_ptr_value(conf->format, prev->format,
                             ngx_http_get_check_status_format_conf(&format));

    return NGX_CONF_OK;
}