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
struct TYPE_2__ {int /*<<< orphan*/  footer_last; int /*<<< orphan*/  header_first; int /*<<< orphan*/  footer; int /*<<< orphan*/  header; int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;
typedef  TYPE_1__ ngx_http_slice_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_http_slice_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_slice_loc_conf_t  *prev = parent;
    ngx_http_slice_loc_conf_t  *conf = child;

    ngx_conf_merge_str_value(conf->begin, prev->begin, "begin");
    ngx_conf_merge_str_value(conf->end, prev->end, "end");
    ngx_conf_merge_str_value(conf->header, prev->header, "");
    ngx_conf_merge_str_value(conf->footer, prev->footer, "");
    ngx_conf_merge_value(conf->header_first, prev->header_first, 1);
    ngx_conf_merge_value(conf->footer_last, prev->footer_last, 1);

    return NGX_CONF_OK;
}